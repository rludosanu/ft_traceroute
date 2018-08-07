/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 16:20:57 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int			parse_opts(s_opts *opts, int argc, char **argv)
{
	int		i;
	char	*p;

	if (argc < 2)
		return (infousage(ERR_USG));
	i = 1;
	while (i < argc)
	{
		p = argv[i];
		// Start hop
		if (ft_strequ(p, "-f"))
		{
			if (ft_isnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
			{
				if ((opts->opt_ttlst = atoi(argv[i++ + 1])) > opts->opt_ttl)
					return (infousage(ERR_TTL));
			}
			else
				return (infousage(ERR_INVARG));
		}
		// Max hops
		else if (ft_strequ(p, "-m"))
		{
			if (ft_isnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
			{
				if ((opts->opt_ttl = atoi(argv[i++ + 1])) < opts->opt_ttlst)
					return (infousage(ERR_TTL));
			}
			else
				return (infousage(ERR_INVARG));
		}
		// Wait time
		else if (ft_strequ(p, "-w"))
		{
			if (ft_isnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
				opts->opt_timeout = atoi(argv[i++ + 1]);
			else
				return (infousage(ERR_INVARG));
		}
		// Probes count
		else if (ft_strequ(p, "-q"))
		{
			if (ft_isnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
				opts->opt_probes = atoi(argv[i++ + 1]);
			else
				return (infousage(ERR_INVARG));
		}
		// Port (used only for UDP)
		else if (ft_strequ(p, "-p"))
		{
			if (ft_isnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
				opts->opt_port = atoi(argv[i++ + 1]);
			else
				return (infousage(ERR_INVARG));
		}
		else if (*p == '-')
		{
			p++;
			while (*p != '\0')
			{
				if (*p == 'h')
					return (infousage(ERR_USG));
				else if (*p == 'I')
					opts->opt_proto = IPPROTO_ICMP;
				else if (*p == 'U')
					opts->opt_proto = IPPROTO_UDP;
				else
					return (infousage(ERR_INVOPT));
				p++;
			}
		}
		else
		{
			if (ft_isnumber(argv[i]))
				return (infousage(ERR_INVARG));
			opts->destination = argv[i];
			return (0);
		}
		i++;
	}
	return (infousage(ERR_USG));
}
