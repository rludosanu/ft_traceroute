# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rludosan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 10:26:56 by rludosan          #+#    #+#              #
#    Updated: 2017/06/07 14:07:30 by rludosan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC		=	ft_traceroute
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
SRC			=	main\
				ft_isnumber\
				ft_memcpy\
				ft_memset\
				ft_strequ\
				checksum\
				infousage\
				parse_opts\
				read_hostname\
				read_packet\
				resolve_host\
				send_packet\
				timeval_diff
OBJ			=	$(addsuffix .o, $(SRC))

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

.PHONY: all clean fclean re
