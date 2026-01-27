/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:44:37 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/27 11:44:28 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_exec(t_shell *shell, char **path, t_cmd *cmd)
{
	if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		(free_double(path), exit(builtin_pwd(cmd, shell)));
	else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		(free_double(path), exit(builtin_echo(cmd, shell)));
	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		(free_double(path), exit(builtin_cd(cmd, shell)));
	
	
}

int	builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	char	cwd[4096];
	
	if (cmd->argv[1])
		return (ft_putstr_fd("too many arg\n", 2), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (delete_shell(shell), ft_putendl_fd(cwd, 1), 0);
	else
		return (delete_shell(shell), ft_putstr_fd("pwd error\n", 2), 1);
}

int	builtin_echo(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n", ft_strlen(cmd->argv[i])) == 0)
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
	return (delete_shell(shell), 0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd)
	{
		if (chdir(get_user_dir(shell->env)) == NULL)
			return (ft_putstr_fd("CD ERROR\n", 2), 1);
	}
	if (chdir(cmd->argv[1]) == NULL)
		return (ft_putstr_fd("CD ERROR\n", 2), 1);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (cmd->argv[1])
		return (127);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 0);
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
}
