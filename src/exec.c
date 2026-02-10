/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:46:24 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/10 11:17:25 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	simple_exec(t_shell *shell, char **path, t_cmd *cmd, char *command)
{
	signal(SIGQUIT, sigquit_handler2);
	if (apply_redirection(cmd) == false)
		(ft_putendl_fd("REDIRECT ERR", 2), delete_shell(shell, path), exit(2));
	if (cmd && cmd->argv && cmd->argv[0])
	{
		command = valid_command(cmd->argv[0], path);
		if (!command)
			simple_exec_no_path(shell, cmd, path);
		if (access(command, X_OK) == -1)
		{
			(perror(command), delete_shell(shell, path));
			(free(command), exit(126));
		}
		(execve(command, cmd->argv, shell->env), ft_putendl_fd("EXEC ERR", 2));
		(delete_shell(shell, path), free(command), exit(127));
	}
	if (!cmd || !cmd->argv || !cmd->argv[0])
	{
		if (path)
			free_double(path);
		(delete_shell(shell, NULL), exit(0));
	}
	if (!path)
		(delete_shell(shell, NULL), exit(127));
}

void	pipex_out(t_cmd *cmd, char **path, t_shell *shell, int pipe_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("FORK ERROR\n", 2));
	else if (pid == 0)
	{
		status = shell->exit_status;
		if (dup2(pipe_out, 0) == -1)
			(ft_putstr_fd("PIPE ERROR\n", 2), close(pipe_out), exit(2));
		close(pipe_out);
		if (builtin_exec(shell, cmd, path) == false)
			simple_exec(shell, path, cmd, NULL);
		(free_double(path), delete_shell(shell, NULL), exit(status));
	}
	close(pipe_out);
	(wait_and_sig(pid, shell), get_clean_status(shell));
}

void	pipex_mid(t_cmd *cmd, char **path, t_shell *shell, int pip_in)
{
	pid_t	pid;
	int		pip[2];
	int		status;

	if (pipe(pip) == -1)
		return (ft_putstr_fd("PIPE ERROR\n", 2));
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("FORK ERROR\n", 2));
	else if (pid == 0)
	{
		status = shell->exit_status;
		if (dup2(pip_in, 0) == -1 || dup2(pip[1], 1) == -1)
			(ft_putstr_fd("PIPE ERROR\n", 2), close(pip[0]), exit(2));
		(close(pip[0]), close(pip[1]), close(pip_in));
		if (builtin_exec(shell, cmd, path) == false)
			simple_exec(shell, path, cmd, NULL);
		(free_double(path), delete_shell(shell, NULL), exit(status));
	}
	(close(pip[1]), close(pip_in));
	if (!cmd->next->next)
		pipex_out(cmd->next, path, shell, pip[0]);
	else
		pipex_mid(cmd->next, path, shell, pip[0]);
	(wait_and_sig(pid, shell), get_clean_status(shell));
}

void	pipex(t_shell *shell, char **path, int status)
{
	pid_t	pid;
	int		pip[2];

	if (pipe(pip) == -1)
		return (ft_putstr_fd("PIPE ERROR\n", 2));
	pid = fork();
	if (pid == -1)
		return (close(pip[0]), close(pip[1]), ft_putstr_fd("FORK ERROR\n", 2));
	else if (pid == 0)
	{
		if (dup2(pip[1], 1) == -1)
			(ft_putstr_fd("DUP2 ERROR\n", 2), close(pip[0]), close(pip[1]),
				exit(2));
		(close(pip[0]), close(pip[1]));
		if (builtin_exec(shell, shell->cmd, path) == false)
			simple_exec(shell, path, shell->cmd, NULL);
		(free_double(path), delete_shell(shell, NULL), exit(status));
	}
	close(pip[1]);
	if (!shell->cmd->next->next)
		pipex_out(shell->cmd->next, path, shell, pip[0]);
	else
		pipex_mid(shell->cmd->next, path, shell, pip[0]);
	(wait_and_sig(pid, shell), get_clean_status(shell));
}

void	exec_shell(t_shell *shell)
{
	char	**path;
	pid_t	pid;

	path = get_path(shell->env);
	if (!shell->cmd->next)
	{
		if (builtin_exec(shell, shell->cmd, path) == false)
		{
			pid = fork();
			if (pid == -1)
				return (ft_putstr_fd("FORK ERROR\n", 2), free_double(path));
			else if (pid == 0)
				simple_exec(shell, path, shell->cmd, NULL);
			(wait_and_sig(pid, shell), get_clean_status(shell));
		}
	}
	else
		pipex(shell, path, shell->exit_status);
	if (path)
		free_double(path);
}
