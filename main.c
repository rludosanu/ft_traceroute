/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 17:31:11 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int						main(int argc, char **argv)
{
	int					sock_udp;
	int					sock_icmp;
	s_opts				opts;
	int					n_probes;
	char				host[INET_ADDRSTRLEN + 1];
	struct sockaddr_in	*saddr;
	struct timeval		tv_send;
	struct timeval		tv_select;
	fd_set				readfs;
	int					ret;
	int 				retpkt;

	// Init sockets
	sock_udp = -1;
	sock_icmp = -1;

	// Default options
	opts.opt_reuse = 1;
	opts.opt_ttl = 30;
	opts.opt_ttlst = 1;
	opts.opt_probes = 3;
	opts.opt_timeout = 5;
	opts.opt_port = 33434;
	opts.opt_proto = IPPROTO_UDP;

	// Parse options
	if (parse_opts(&opts, argc, argv) == -1)
		return (0);

	// Resolve hostname
	if (!(saddr = resolve_host(opts.destination)))
		return (-1);

	// Create UDP socket
	if (opts.opt_proto == IPPROTO_UDP)
	{
		if ((sock_udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
			return (infousage(ERR_SOCK));
		setsockopt(sock_udp, SOL_SOCKET, SO_REUSEADDR, &(opts.opt_reuse), sizeof(opts.opt_reuse));
	}

	// Create ICMP socket
	if ((sock_icmp = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		return (infousage(ERR_SOCK));
	setsockopt(sock_icmp, SOL_SOCKET, SO_REUSEADDR, &(opts.opt_reuse), sizeof(opts.opt_reuse));

	// Print first line
	read_hostname(&(saddr->sin_addr), (char *)&(host));
	printf("ft_traceroute to %s (%s), %d hops max\n", opts.destination, host, opts.opt_ttl);

	// Start looping on probes
	while (opts.opt_ttlst <= opts.opt_ttl)
	{
		// TTL socket option
		setsockopt((opts.opt_proto == IPPROTO_UDP) ? sock_udp : sock_icmp, IPPROTO_IP, IP_TTL, &(opts.opt_ttlst), sizeof(opts.opt_ttlst));

		// Listen for echo replies
		n_probes = 0;
		while (n_probes < opts.opt_probes)
		{
			// Send one probe
			send_packet(opts.opt_proto, (opts.opt_proto == IPPROTO_UDP) ? sock_udp : sock_icmp, opts.opt_port, saddr, &tv_send);
			
			// Timeout for incoming packets
			tv_select.tv_sec = (long)opts.opt_timeout;
			tv_select.tv_usec = 0;

			// FD sets
			FD_ZERO(&readfs);
			FD_SET(sock_icmp, &readfs);

			// Read probe
			ret = select(sock_icmp + 1, &readfs, NULL, NULL, &tv_select);
			if (ret < 0)
			{
				printf("ft_traceroute: error: select failed\n");
				if (saddr)
					free(saddr);
				close(sock_udp);
				close(sock_icmp);
				exit(0);
			}
			else if (ret == 0)
			{
				if (n_probes == 0)
					printf("%2d ", opts.opt_ttlst);
				printf(" *");
			}
			if (FD_ISSET(sock_icmp, &readfs))
			{
				retpkt = read_packet(sock_icmp, opts.opt_ttlst, n_probes, &tv_send);
				if ((retpkt == 0 || retpkt == 3) && (n_probes + 1 == opts.opt_probes))
				{
					printf("\n");
					close(sock_udp);
					close(sock_icmp);
					if (saddr)
						free(saddr);
					exit(0);
				}
			}
			n_probes++;
		}
		printf("\n");
		opts.opt_ttlst++;
		opts.opt_port++;
	}
	close(sock_udp);
	close(sock_icmp);
	if (saddr)
		free(saddr);
	return (0);
}
