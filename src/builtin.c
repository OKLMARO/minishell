/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:44:37 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/07 15:07:12 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	builtin_parsing(t_shell *shell, t_cmd *cmd)
{
	if (cmd && cmd->argv)
	{
		if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
			return (shell->exit_status = builtin_pwd(cmd), true);
		else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
			return (shell->exit_status = builtin_echo(cmd), true);
		else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
			return (shell->exit_status = builtin_cd(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
			return (shell->exit_status = builtin_env(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
			return (shell->exit_status = builtin_export(cmd, shell, 0), true);
		else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
			return (shell->exit_status = builtin_unset(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
			return (true);
		return (false);
	}
	return (false);
}

bool	builtin_exec(t_shell *shell, t_cmd *cmd, char **path)
{
	int		std_in;
	int		std_out;
	bool	is_builtin;

	std_in = dup(0);
	std_out = dup(1);
	if (std_in == -1 || std_out == -1)
		return (close(std_in), close(std_out),
			ft_putendl_fd("dup error", 2), false);
	if (apply_redirection(cmd) == false)
		return (close(std_in), close(std_out), false);
	is_builtin = builtin_parsing(shell, cmd);
	if (dup2(std_in, 0) == -1 || dup2(std_out, 1) == -1)
		return (close(std_in), close(std_out),
			ft_putendl_fd("dup2 error", 2), false);
	close(std_in);
	close(std_out);
	if (cmd->argv && ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		builtin_exit(cmd, shell, path);
	return (is_builtin);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell, char **path)
{
	int	exit_value;

	if (cmd->argv[1])
	{
		if (cmd->argv[2])
			return (ft_putendl_fd("too many arg", 2), 1);
		exit_value = ft_atoi(cmd->argv[1]);
		if (exit_value == -1)
			exit_value = 2;
		free_double(path);
		delete_shell(shell, NULL);
		exit(exit_value);
	}
	free_double(path);
	delete_shell(shell, NULL);
	exit(0);
	return (0);
}

int	builtin_pwd(t_cmd *cmd)
{
	char	cwd[4096];

	if (cmd->argv[1])
		return (ft_putstr_fd("too many arg\n", 2), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_putendl_fd(cwd, 1), 0);
	else
		return (ft_putstr_fd("pwd error\n", 2), 1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n",
			ft_strlen(cmd->argv[i])) == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putendl_fd("", 1);
	return (0);
}
