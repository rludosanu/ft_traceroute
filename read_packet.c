/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 15:45:32 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int						read_packet(int sock, int hops, int probes, struct timeval *tv_send)
{
	struct sockaddr_in	from;
	socklen_t			fromlen;
	char				buf[MAX_DGRAM_SIZE];
	char 				*ptr;
	struct timeval		tv_read;
	double				tv_delta;
	struct ip			*ip;
	struct icmp			*icmp;
	int 				n;
	char 				host[INET_ADDRSTRLEN + 1];

	ft_memset(&buf, 0, MAX_DGRAM_SIZE);
	if ((n = recvfrom(sock, &buf, MAX_DGRAM_SIZE, 0, (struct sockaddr *)&from, &fromlen)) > 0)
	{
		ptr = (char *)&buf;
		ip = (struct ip *)ptr;
		icmp = (struct icmp *)(ptr + (ip->ip_hl * 4));

		gettimeofday(&tv_read, NULL);
		tv_delta = timeval_diff(tv_send, &tv_read);

		if (probes == 0)
			printf("%2d  %s", hops, read_hostname(&(ip->ip_src), (char *)&(host)));
		printf("  %.3f ms", tv_delta);
		return (icmp->icmp_type);
	}
	return (-1);
}
