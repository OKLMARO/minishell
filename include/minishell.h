#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef enum {
	REDIRECT_OUT,
	REDIRECT_IN,
	HERE_DOC,
	APPEND,
	WORD,
	PIPE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*type;
	t_token			*next;
}					t_token;

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		init_token(t_list **list);
char	*find_first_adr(char *res[]);
char	*is_token(t_list *list, char *token);
int		builtin_cd(char **args, char **env);
int		builtin_echo(char **args);
void	builtin_pwd(void);
void	free_double(char **tab_str);
char	*get_user_dir(char **env);
char	**get_path(char **env);
void	sigint_handler(int signo);
void	sigint_handler2(int signo);
void	sigquit_handler2(int signo);
int		open_redirect_out(char **args, int i, int *file, t_list *list);
int		open_redirect_in(char **args, int i, int *file, t_list *list);
int		redirect_in(char **args, int i, t_list *list);
int		redirect_out(char **args, int i, t_list *list);

#endif