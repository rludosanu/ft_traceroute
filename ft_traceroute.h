/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/26 15:02:57 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# define ERR_USG 1
# define ERR_INVOPT 2
# define ERR_INVARG 3
# define ERR_SOCK 4
# define ERR_TTL 5
# define ERR_PROTO 6

# define MAX_DGRAM_SIZE 512

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/in_systm.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/time.h>

/*
** Options
*/

typedef struct          t_opts
{
    int	                opt_reuse;
	int				    opt_ttl;
    int	                opt_ttlst;
	int				    opt_timeout;
	int				    opt_probes;
	int				    opt_port;
	int				    opt_proto;
    char                *destination;
}                       s_opts;

/*
** Internet checksum
*/

unsigned short			checksum(unsigned short *ptr, int nbytes);

/*
** Parse CLI arguments
*/
	
int						parse_opts(s_opts *opts, int argc, char **argv);

/*
** Libft utils
*/
	
int						ft_isnumber(char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);
int						ft_strequ(char *s1, char *s2);

/*
** Usage informations and errors
*/
	
int						infousage(int e);

/*
** Host resolving
*/
	
char					*read_hostname(struct in_addr *iaddr, char *host);
struct sockaddr_in		*resolve_host(char *host);

/*
** Read/Send packets
*/

int						read_packet(int sock, int hops, int probes, struct timeval *tv_send);
void					send_packet(int proto, int sock, int port, struct sockaddr_in *saddr, struct timeval *tv_send);
void 					send_packet_udp(int sock, int port, struct sockaddr_in *saddr, struct timeval *tv_send);
void 					send_packet_icmp(int sock, struct sockaddr_in *saddr, struct timeval *tv_send);

/*
** RTT calculation
*/

double					timeval_diff(struct timeval *tv_1, struct timeval *tv_2);

#endif
