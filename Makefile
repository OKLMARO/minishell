# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 10:41:12 by oamairi           #+#    #+#              #
#    Updated: 2026/01/21 10:00:12 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	=	src/builtin.c src/env.c src/exec.c src/exec_utils.c src/expand.c \
			src/lexer_utils.c src/lexer.c src/main.c src/parser.c src/redirect.c \
			src/t_cmd_utils.c src/t_token_utils.c src/utils.c

OBJS	= $(SRCS:.c=.o)

LIBFT 	= include/libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C include/libft bonus
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) include/libft/libft.a -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C include/libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C include/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
