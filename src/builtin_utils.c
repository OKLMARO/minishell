/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 20:43:18 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/01 20:47:35 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;

	if (!cmd->argv[1])
		return (ft_putendl_fd("not enough arg", 2), 1);
	i = 1;
	while (cmd->argv[i])
	{
		j = 0;
		while (shell->env[j])
		{
			if (ft_strncmp(cmd->argv[i], shell->env[j], ft_strlen(cmd->argv[i]))
				== 0 && shell->env[j][ft_strlen(cmd->argv[i])] == '=')
			{
				remove_env(shell, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*usr_home;

	if (!cmd->argv[1])
	{
		usr_home = get_user_dir(shell->env);
		if (!usr_home)
			return (ft_putendl_fd("HOME ERROR", 2), 1);
		if (chdir(usr_home) == -1)
			return (free(usr_home), ft_putstr_fd("CD ERROR\n", 2), 1);
		return (free(usr_home), 0);
	}
	if (chdir(cmd->argv[1]) == -1)
		return (ft_putstr_fd("CD ERROR\n", 2), 1);
	return (0);
}
