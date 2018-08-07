/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeval_diff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/25 19:32:22 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

double		timeval_diff(struct timeval *tv_1, struct timeval *tv_2)
{
	return ((double)(((tv_2->tv_sec - tv_1->tv_sec) * 1000000) + (tv_2->tv_usec - tv_1->tv_usec)) / 1000);
}
