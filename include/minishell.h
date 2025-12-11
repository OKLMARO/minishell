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
# include <stdbool.h>
# include "libft/libft.h"

typedef enum {
	REDIRECT_OUT,
	REDIRECT_IN,
	HERE_DOC,
	APPEND,
	WORD,
	PIPE
}	t_token_type;

typedef enum {
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	t_quote_type	quote;
	struct s_token	*next;
}					t_token;

typedef struct s_redirect
{
	t_token_type		type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char			**argv;
	t_redirect		*redirects;
	struct s_cmd	*next;
}					t_cmd;

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
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_tokennew(t_token_type type, void *s, t_quote_type quote);
t_token	*lexer_word(t_token_type type, t_token **list, char *buffer, t_quote_type quote);
bool	make_lexer_single_quote(char *input, t_token **list, int *i, char *buffer);
bool	make_lexer_double_quote(char *input, t_token **list, int *i, char *buffer);
void	make_lexer(t_token_type type, t_token **list, char *buffer, t_quote_type quote);
void	add_to_buffer(char *buffer, int *i_buffer, char *input, int i);
void	ft_redirectadd_back(t_redirect **lst, t_redirect *new);
bool	lexer_compare(char *input, t_token **list, int *i, char *buffer);
t_token	*lexer(char *input);
t_cmd	*ft_cmdnew(void);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);

#endif