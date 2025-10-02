/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:45:34 by oamairi           #+#    #+#             */
/*   Updated: 2025/10/02 13:19:41 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_token(t_list *list)
{
	ft_lstadd_front(&list, ft_lstnew("<"));
	ft_lstadd_front(&list, ft_lstnew(">"));
	ft_lstadd_front(&list, ft_lstnew("<<"));
	ft_lstadd_front(&list, ft_lstnew(">>"));
	ft_lstadd_front(&list, ft_lstnew("|"));
	ft_lstadd_front(&list, ft_lstnew("$"));
	return (0);
}

char	*is_token(t_list *list, char *token)
{
	t_list	*temp;
	int		i;

	
	while (i > 0)
	{	
		temp = list;
		while (temp)
		{
			if (ft_strstr(token, temp->content, ft_strlen(temp->content)))
				return (ft_strstr(token, temp->content, ft_strlen(temp->content)));
			temp = temp->next;
		}
	}
	return (NULL);
}

char    *get_user_dir(char **env)
{
	int		i;
	char	*user_dir;

	i = 0;
	user_dir = NULL;
	while (env[i])
	{
		if (ft_strncmp("USER_ZDOTDIR=", env[i], 13) == 0)
		{
			user_dir = ft_strdup(env[i] + 13);
			if (!user_dir)
				return (NULL);
		}
		i++;
	}
	return (user_dir);
}

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
		i++;
	}
	return (path);
}

char	*valid_command(char *cmd, char **path)
{
	char	*valid_cmd;
	char	*temp;
	int		i;

	i = 0;
	valid_cmd = ft_strjoin("/", cmd);
	if (!valid_cmd)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], valid_cmd);
		if (!temp)
			return (free(valid_cmd), NULL);
		if (access(temp, X_OK) == 0)
			return (free(valid_cmd), temp);
		free(temp);
		i++;
	}
	return (free(valid_cmd), NULL);
}

int	make_storage(char ***cmd, char *argv, char **all_cmd, char **path)
{
	*cmd = ft_split(argv, ' ');
	if (!*cmd)
		return (perror("Malloc crash"), 0);
	*all_cmd = valid_command(*cmd[0], path);
	if (!*all_cmd)
		return (perror("Commande introuvable ou non executable"), 2);
	return (1);
}

int builtin_cd(char **args, char **env)
{
	if (!args[1])
	{
		args[1] = get_user_dir(env);
	}
	if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		return -1;
	}
	return 0;
}

void sigint_handler(int signo)
{
	(void)signo;

	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void sigint_handler2(int signo)
{
	(void)signo;

	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void sigquit_handler2(int signo)
{
	(void)signo;

	write(1, "Quit (core dumped)", 19);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	pid_t	pid;
	char	**args;
	char	**path;
	char	**cmd;
	char	*all_cmd;
	t_list	*token;
	int		i;
	
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	token = malloc(sizeof(t_list));
	init_token(token);
	path = get_path(env);
	if (!path)
		return (ft_putstr_fd("Env error", 2), 2);
	while (1)
	{
		input = readline("minishell $>");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strncmp(input, "exit", 15) == 0)
		{
			ft_putstr_fd("exit", 1);
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		if (args[0] && ft_strncmp(args[0], "cd", 3) == 0)
		{
			if (builtin_cd(args, env) == -1)
				return (1);
		}
		i = 0;
		while (args[i])
		{
			if(is_token(token, args[i]))
			{
				if (ft_strncmp(is_token(token, args[i]), "|", 3))
					pipex(...);
				else if (ft_strncmp(is_token(token, args[i]), "<", 3))
					redirect_in(...);
				else if (ft_strncmp(is_token(token, args[i]), ">", 3))
					redirect_out(...);
				else if (ft_strncmp(is_token(token, args[i]), "<<", 3))
					jsp(...);
				else if (ft_strncmp(is_token(token, args[i]), ">>", 3))
					redirect_out_append(...);
			}
			i++;
		}
		pid = fork();
		if (pid == 0)
		{
			make_storage(&cmd, input, &all_cmd, path);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (execve(all_cmd, cmd, env) == -1)
			{
				ft_putstr_fd("exec error", 2);
				return (1);
			}
		}
		else if (pid > 0)
		{
			signal(SIGQUIT, sigquit_handler2);
			signal(SIGINT, sigint_handler2);
			waitpid(pid, NULL, 0);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, sigint_handler);
		}
		else
		{
			ft_putstr_fd("fork error", 2);
			return (1);
		}
		free(input);
	}
	return (0);
}
