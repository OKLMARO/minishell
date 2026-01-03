/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:46:24 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/03 13:46:35 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	apply_redirection(t_cmd *cmd)
{
	
}

void	simple_exec(t_cmd *cmd, char **path, char **env)
{
	pid_t	pid;
	char	*command;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("FORK ERROR", 2));
	else if (pid == 0)
	{
		if (apply_redirection(cmd) == -1)
			(ft_putstr_fd("REDIRECT ERROR", 2), exit(2));
		command = valid_command(cmd->argv[0], path);
		if (!command)
			(ft_putstr_fd("PATH ERROR", 2), exit(127));
		execve(command, cmd->argv, env);
		ft_putstr_fd("COMMAND ERROR", 2);
		free(command);
		exit(126);
	}
	waitpid(pid, NULL, 0);
}

void	exec_shell(t_cmd *cmd, char **env)
{
	char	**path;

	if (!cmd)
		return ;
	path = get_path(env);
	if (!path)
		return (ft_putstr_fd("ENV ERROR", 2));
	else if (!cmd->next)
		simple_exec(cmd, path, env);
	else if (!cmd->next->next)
		pipex(cmd, path, env);
	else
		multi_exec(cmd, path, env);
	free_double(path);
}
