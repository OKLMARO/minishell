# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 10:41:12 by oamairi           #+#    #+#              #
#    Updated: 2026/02/01 20:52:30 by oamairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	=	src/builtin.c src/env.c src/exec.c src/exec_utils.c src/expand.c \
			src/lexer_utils.c src/lexer.c src/main.c src/parser.c src/redirect.c \
			src/t_cmd_utils.c src/t_token_utils.c src/utils.c src/shell.c \
			src/builtin_utils.c src/env_builtin.c

OBJS	= $(SRCS:.c=.o)

SUPP_FILE = readline.supp

LIBFT 	= include/libft/libft.a

all: $(NAME) $(SUPP_FILE)


$(SUPP_FILE):
	@echo "{" > $(SUPP_FILE)
	@echo "   ignore_readline_leaks" >> $(SUPP_FILE)
	@echo "   Memcheck:Leak" >> $(SUPP_FILE)
	@echo "   ..." >> $(SUPP_FILE)
	@echo "   obj:*/libreadline.so.*" >> $(SUPP_FILE)
	@echo "}" >> $(SUPP_FILE)
	@echo "" >> $(SUPP_FILE)
	@echo "{" >> $(SUPP_FILE)
	@echo "   ignore_readline_add_history" >> $(SUPP_FILE)
	@echo "   Memcheck:Leak" >> $(SUPP_FILE)
	@echo "   ..." >> $(SUPP_FILE)
	@echo "   fun:add_history" >> $(SUPP_FILE)
	@echo "}" >> $(SUPP_FILE)
	@echo "" >> $(SUPP_FILE)
	@echo "{" >> $(SUPP_FILE)
	@echo "   ignore_readline_using_history" >> $(SUPP_FILE)
	@echo "   Memcheck:Leak" >> $(SUPP_FILE)
	@echo "   ..." >> $(SUPP_FILE)
	@echo "   fun:using_history" >> $(SUPP_FILE)
	@echo "}" >> $(SUPP_FILE)
	@echo "Suppression file created: $(SUPP_FILE)"

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
	rm -f $(NAME) $(SUPP_FILE)

re: fclean all

supp: all
	valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip=/bin/*,/usr/bin/*,/usr/local/bin/* --suppressions=$(SUPP_FILE) -s ./$(NAME)

.PHONY: all clean fclean re
