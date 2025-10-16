NAME	= minishell

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -g3

SRCS	= minishell.c

OBJS	= $(SRCS:.c=.o)

LIBFT 	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft bonus
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lreadline

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
