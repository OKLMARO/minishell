/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 20:45:56 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/14 14:07:24 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (cmd->argv[1])
		return (127);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
	return (0);
}

bool	add_env(t_cmd *cmd, t_shell *shell, int i)
{
	int		k;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (ft_strlenlen(shell->env) + 2));
	if (!new_env)
		return (ft_putendl_fd("Malloc error", 2), false);
	k = 0;
	while (shell->env && shell->env[k])
	{
		new_env[k] = ft_strdup(shell->env[k]);
		if (!new_env[k])
			return (free_double(new_env), perror("Malloc error"), false);
		k++;
	}
	new_env[k] = ft_strdup(cmd->argv[i]);
	new_env[k + 1] = NULL;
	free_double(shell->env);
	shell->env = new_env;
	return (true);
}

int	add_to_env(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		j;

	i = 1;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '=')
			return (ft_putendl_fd("need a valid identifier", 2), 1);
		j = 1;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '=')
			{
				if (replace_env(cmd, shell, i) == false)
				{
					if (add_env(cmd, shell, i) == false)
						return (1);
				}
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell, int i)
{
	char	*temp;

	if (!cmd->argv[1])
	{
		i = 0;
		while (shell->env && shell->env[i] && shell->env[i + 1])
		{
			if (ft_strncmp(shell->env[i], shell->env[i + 1], LONG_MAX) > 0)
			{
				temp = shell->env[i];
				shell->env[i] = shell->env[i + 1];
				shell->env[i + 1] = temp;
				i = 0;
			}
			i++;
		}
		i = 0;
		while (shell->env && shell->env[i])
		{
			ft_putendl_fd(shell->env[i], 1);
			i++;
		}
		return (0);
	}
	return (add_to_env(cmd, shell));
}

void	remove_env(t_shell *shell, int j)
{
	int		i;
	int		k;
	char	**new_env;

	new_env = malloc(sizeof(char *) * ft_strlenlen(shell->env));
	if (!new_env)
		return ;
	i = 0;
	k = 0;
	while (shell->env[i])
	{
		if (i == j)
			i++;
		else
		{
			new_env[k] = ft_strdup(shell->env[i]);
			if (!new_env[k])
				return (free_double(new_env));
			i++;
			k++;
		}
	}
	new_env[k] = NULL;
	free_double(shell->env);
	shell->env = new_env;
}
