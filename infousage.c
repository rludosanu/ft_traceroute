/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infousage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 17:15:11 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int		infousage(int e)
{
	if (e == ERR_USG)
		printf("Usage: ./ft_traceroute [-h] [-f first_ttl] [-m max_ttl] [-w waittime] [-q nqueries] [-I (icmp)] [-U (udp)] [-p port] host\n");
	else if (e == ERR_INVOPT)
		printf("ft_traceroute: unknown option\n");
	else if (e == ERR_INVARG)
		printf("ft_traceroute: invalid argument\n");
	else if (e == ERR_SOCK)
		printf("ft_traceroute: unable to create icmp socket\n");
	else if (e == ERR_TTL)
		printf("ft_traceroute: first ttl (-f) cannot be greater than max ttl (-m)\n");
	return (-1);
}
