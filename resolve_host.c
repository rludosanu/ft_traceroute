/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_host.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 14:42:26 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct sockaddr_in 		*resolve_host(char *host)
{
	struct addrinfo		*res;
	struct addrinfo		hints;
	struct sockaddr_in	*saddr;
	int					ret;

	if (host == NULL)
		return (NULL);

	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;

	saddr = NULL;

	if ((ret = getaddrinfo(host, NULL, &hints, &res)) == 0)
	{
		if ((saddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in))))
			ft_memcpy(saddr, res->ai_addr, sizeof(struct sockaddr_in));
		freeaddrinfo(res);
	}

	if (ret != 0 || saddr == NULL)
		printf("ft_traceroute: unknown host %s\n", host);

	return (saddr);
}
