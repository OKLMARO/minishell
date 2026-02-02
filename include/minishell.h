/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:35:58 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/02 16:37:54 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	REDIRECT_OUT,
	REDIRECT_IN,
	HERE_DOC,
	APPEND,
	WORD,
	PIPE
}	t_token_type;

typedef enum e_quote_type
{
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
	t_quote_type	*quote;
	t_redirect		*redirects;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_cmd	*cmd;
	char	**env;
	t_token	*token;
	int		exit_status;
	int		raw_statuts;
}			t_shell;

extern int	g_sv;

t_cmd	*ft_cmdnew(void);
t_shell	*make_shell(void);
t_token	*lexer(char *input);
void	sigchild(int signo);
char	**get_path(char **env);
int		builtin_pwd(t_cmd *cmd);
int		builtin_echo(t_cmd *cmd);
int		ft_strlenlen(char **lst);
int		init_token(t_list **list);
char	*get_user_dir(char **env);
void	sigint_handler(int signo);
void	sigint_handler2(int signo);
void	ft_cmddestroy(t_cmd **lst);
void	exec_shell(t_shell *shell);
void	sigquit_handler2(int signo);
void	ft_putnbr_fd(int n, int fd);
void	free_double(char **tab_str);
void	delete_shell(t_shell *shell);
char	*find_first_adr(char *res[]);
void	ft_putstr_fd(char *s, int fd);
bool	apply_redirection(t_cmd *cmd);
void	ft_tokendestroy(t_token **lst);
void	get_clean_status(t_shell *shell);
void	do_heredoc(t_shell *shell, int i);
void	remove_env(t_shell *shell, int j);
char	*is_token(t_list *list, char *token);
void	ft_redirectdestroy(t_redirect **lst);
int		builtin_cd(t_cmd *cmd, t_shell *shell);
int		builtin_cd(t_cmd *cmd, t_shell *shell);
char	*valid_command(char *cmd, char **path);
void	wait_and_sig(pid_t pid, t_shell *shell);
int		builtin_env(t_cmd *cmd, t_shell *shell);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int		builtin_env(t_cmd *cmd, t_shell *shell);
int		builtin_unset(t_cmd *cmd, t_shell *shell);
bool	copy_env_in_shell(t_shell *shell, char **env);
int		redirect_in(char **args, int i, t_list *list);
void	ft_tokenadd_back(t_token **lst, t_token *new);
int		redirect_out(char **args, int i, t_list *list);
int		builtin_export(t_cmd *cmd, t_shell *shell, int i);
t_cmd	*parser(t_token *token, int result, t_token	*temp);
void	my_exit(t_cmd **cmd, t_token **token, char *string);
int		builtin_exit(t_cmd *cmd, t_shell *shell, char **path);
bool	builtin_exec(t_shell *shell, t_cmd *cmd, char **path);
void	ft_redirectadd_back(t_redirect **lst, t_redirect *new);
char	*expand_varialbes(t_cmd *cmd_list, t_shell *shell, int i);
void	make_lexer(t_token_type type, t_token **list, char *buffer);
t_token	*ft_tokennew(t_token_type type, void *s, t_quote_type quote);
int		open_redirect_in(char **args, int i, int *file, t_list *list);
int		open_redirect_out(char **args, int i, int *file, t_list *list);
void	add_to_buffer(char *buffer, int *i_buffer, char *input, int i);
bool	lexer_compare(char *input, t_token **list, int *i, char *buffer);
int		make_storage(char ***cmd, char *argv, char **all_cmd, char **path);
bool	make_lexer_single_quote(char *input, t_token **list,
			int *i, char *buffer);
bool	make_lexer_double_quote(char *input, t_token **list,
			int *i, char *buffer);
t_token	*lexer_word(t_token_type type, t_token **list, char *buffer,
			t_quote_type quote);

#endif
