NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= src/*

OBJS	= $(SRCS:.c=.o)

LIBFT 	= include/libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft bonus
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) include/libft/libft.a -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
