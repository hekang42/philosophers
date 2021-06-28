# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hekang <hekang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/14 00:08:03 by hekang            #+#    #+#              #
#    Updated: 2021/06/28 18:15:24 by hekang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c philo.c ft_atoi.c monitor.c
SRCDIR	= ./srcs/
SRCS 	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

INCDIR	= ./includes/

NAME	= philo

GCC 	= GCC
GCCFLAG = -Wall -Werror -Wextra -g
#  -fsanitize=address
RM 		= rm -f

%.o:		%.c
		$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME): 	$(OBJS)
		$(GCC) $(GCCFLAG) -I$(INCDIR) -o $(NAME) $(OBJS)

all:		$(NAME)

bonus:		all

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
