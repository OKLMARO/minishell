# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/27 15:28:05 by oamairi           #+#    #+#              #
#    Updated: 2025/09/27 15:49:53 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RCS		=		src/minishell.c

OBJS	=		$(SRCS:.c=.o)

NAME	=		minishell

RM		=		rm -fr

CC		=		cc

CFLAGS	=		-Wall -Wextra -Werror

LIBFT	=		include/libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C include/libft bonus
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C include/libft clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C include/libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re