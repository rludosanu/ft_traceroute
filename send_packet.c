/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 14:47:06 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

/*
** Sends a probe
*/

void					send_packet(int proto, int sock, int port, struct sockaddr_in *saddr, struct timeval *tv_send)
{
	if (proto == IPPROTO_UDP)
		send_packet_udp(sock, port, saddr, tv_send);
	else
		send_packet_icmp(sock, saddr, tv_send);
}

/*
** Sends an UDP probe
*/

void 					send_packet_udp(int sock, int port, struct sockaddr_in *saddr, struct timeval *tv_send)
{
	char				packet[60];
	struct sockaddr_in	sin;

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = saddr->sin_addr.s_addr;
	ft_memset(&(sin.sin_zero), 0, sizeof(sin.sin_zero));

	ft_memset(&packet, 0, 60);
	gettimeofday(tv_send, NULL);

	sendto(sock, packet, 60, 0, (struct sockaddr *)&sin, sizeof(sin));
}

/*
** Sends an ICMP probe
*/

void 					send_packet_icmp(int sock, struct sockaddr_in *saddr, struct timeval *tv_send)
{
	struct icmp 		*icmp;
	char				*packet;
	size_t				packet_size;
	struct sockaddr_in	sin;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = saddr->sin_addr.s_addr;
	ft_memset(&(sin.sin_zero), 0, sizeof(sin.sin_zero));

	packet_size = sizeof(struct icmp);
	if (!(packet = (char *)malloc(packet_size)))
		return ;

	ft_memset(packet, 0, packet_size);
	gettimeofday(tv_send, NULL);

	icmp = (struct icmp *)packet;
	icmp->icmp_type = 8;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_id = getpid();
	icmp->icmp_seq = 1;
	icmp->icmp_cksum = checksum((unsigned short *)icmp, sizeof(struct icmp));

	sendto(sock, packet, packet_size, 0, (struct sockaddr *)&sin, sizeof(sin));

	free(packet);
}
