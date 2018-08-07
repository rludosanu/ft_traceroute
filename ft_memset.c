/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 14:40:44 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void					*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*t;
	size_t				i;

	t = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*t = c;
		t++;
		i++;
	}
	return (s);
}
