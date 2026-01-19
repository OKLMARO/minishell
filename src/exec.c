/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:46:24 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/19 13:33:35 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	simple_exec(t_cmd *cmd, char **path, char **env)
{
	char	*command;

	command = valid_command(cmd->argv[0], path);
	if (!command)
		(ft_putstr_fd("PATH ERROR", 2), exit(127));
	execve(command, cmd->argv, env);
	ft_putstr_fd("COMMAND ERROR", 2);
	free(command);
	exit(126);
}

void	pipex_out(t_cmd *cmd, char **path, char **env, int pipe_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("FORK ERROR", 2));
	else if (pid == 0)
	{
		if (dup2(pipe_out, 0) == -1)
			(ft_putstr_fd("PIPE ERROR", 2), close(pipe_out), exit(2));
		close(pipe_out);
		if (apply_redirection(cmd) == false)
			(ft_putstr_fd("REDIRECT ERROR", 2), exit(2));
		simple_exec(cmd, path, env);
	}
	close(pipe_out);
	waitpid(pid, NULL, 0);
}

void	pipex_mid(t_cmd *cmd, char **path, char **env, int pip_in)
{
	pid_t	pid;
	int		pip[2];

	if (pipe(pip) == -1)
		return (ft_putstr_fd("PIPE ERROR", 2));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("FORK ERROR", 2));
	else if (pid == 0)
	{
		if (dup2(pip_in, 0) == -1 || dup2(pip[1], 1) == -1)
			(ft_putstr_fd("PIPE ERROR", 2), close(pip[0]), exit(2));
		(close(pip[0]), close(pip[1]), close(pip_in));
		if (apply_redirection(cmd) == false)
			(ft_putstr_fd("REDIRECT ERROR", 2), exit(2));
		simple_exec(cmd, path, env);
	}
	(close(pip[1]), close(pip_in));
	if (!cmd->next->next)
		pipex_out(cmd->next, path, env, pip[0]);
	else
		pipex_mid(cmd->next, path, env, pip[0]);
	waitpid(pid, NULL, 0);
}

void	pipex(t_cmd *cmd, char **path, char **env)
{
	pid_t	pid;
	int		pip[2];

	if (pipe(pip) == -1)
		return (ft_putstr_fd("PIPE ERROR", 2));
	pid = fork();
	if (pid == -1)
		return (close(pip[0]), close(pip[1]), ft_putstr_fd("FORK ERROR", 2));
	else if (pid == 0)
	{
		if (dup2(pip[1], 1) == -1)
			(ft_putstr_fd("DUP2 ERROR", 2), close(pip[0]), close(pip[1]),
				exit(2));
		(close(pip[0]), close(pip[1]));
		if (apply_redirection(cmd) == false)
			(ft_putstr_fd("REDIRECT ERROR", 2), exit(2));
		simple_exec(cmd, path, env);
	}
	close(pip[1]);
	if (!cmd->next->next)
		pipex_out(cmd->next, path, env, pip[0]);
	else
		pipex_mid(cmd->next, path, env, pip[0]);
	waitpid(pid, NULL, 0);
}

void	exec_shell(t_cmd *cmd, char **env)
{
	char	**path;
	pid_t	pid;

	if (!cmd)
		return ;
	path = get_path(env);
	if (!path)
		return (ft_putstr_fd("ENV ERROR", 2));
	else if (!cmd->next)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("FORK ERROR", 2), free_double(path));
		else if (pid == 0)
			simple_exec(cmd, path, env);
		waitpid(pid, NULL, 0);
	}
	else
		pipex(cmd, path, env);
	free_double(path);
}
