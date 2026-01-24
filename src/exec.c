/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:46:24 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/24 18:01:08 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	simple_exec(t_shell *shell, char **path, t_cmd *cmd)
{
	char	*command;

	if (apply_redirection(shell->cmd) == false)
			(ft_putstr_fd("REDIRECT ERROR", 2), exit(2));
	if (cmd && cmd->argv && cmd->argv[0] && path)
	{
		command = valid_command(shell->cmd->argv[0], path);
		if (!command)
		{
			(ft_cmddestroy(&shell->cmd), ft_tokendestroy(&shell->token));
			(free_double(path), ft_putstr_fd("COMMAND NOT FOUND", 2));
			return (free(shell), exit(127));
		}
		execve(command, cmd->argv, shell->env);
		ft_putstr_fd("EXEC ERROR", 2);
		(ft_cmddestroy(&shell->cmd), ft_tokendestroy(&shell->token));
		(free(shell), free_double(path), free(command), exit(127));
	}
}

void	pipex_out(t_cmd *cmd, char **path, t_shell *shell, int pipe_out)
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
		simple_exec(shell, path, cmd);
	}
	close(pipe_out);
	waitpid(pid, NULL, 0);
}

void	pipex_mid(t_cmd *cmd, char **path, t_shell *shell, int pip_in)
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
		simple_exec(shell, path, cmd);
	}
	(close(pip[1]), close(pip_in));
	if (!shell->cmd->next->next)
		pipex_out(cmd->next, path, shell, pip[0]);
	else
		pipex_mid(cmd->next, path, shell, pip[0]);
	waitpid(pid, NULL, 0);
}

void	pipex(t_shell *shell, char **path)
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
		simple_exec(shell, path, shell->cmd);
	}
	close(pip[1]);
	if (!shell->cmd->next->next)
		pipex_out(shell->cmd->next, path, shell, pip[0]);
	else
		pipex_mid(shell->cmd->next, path, shell, pip[0]);
	waitpid(pid, NULL, 0);
}

void	exec_shell(t_shell* shell, char **env)
{
	char	**path;
	pid_t	pid;

	if (!shell->cmd)
		return ;
	path = get_path(env);
	if (!path)
		return (ft_putstr_fd("ENV ERROR", 2));
	else if (!shell->cmd->next)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("FORK ERROR", 2), free_double(path));
		else if (pid == 0)
			simple_exec(shell, path, shell->cmd);
		waitpid(pid, NULL, 0);
	}
	else
		pipex(shell, path);
	free_double(path);
}
