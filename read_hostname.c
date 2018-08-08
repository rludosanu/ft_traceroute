/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 14:43:37 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

char	*read_hostname(struct in_addr *iaddr, char *host)
{
	memset(host, 0, INET_ADDRSTRLEN + 1);
	if (inet_ntop(AF_INET, &(iaddr->s_addr), host, INET_ADDRSTRLEN + 1))
		return (host);
	return (NULL);
}
