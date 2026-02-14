/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:52:13 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/14 14:08:14 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sv;

void	echo_print(t_cmd *cmd, int i, bool newline)
{
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putendl_fd("", 1);
}

bool	replace_env(t_cmd *cmd, t_shell *shell, int k)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	while (shell->env && shell->env[i])
	{
		j = 0;
		while (shell->env[i][j] == cmd->argv[k][j] && cmd->argv[k][j] != '=')
			j++;
		if (shell->env[i][j] == '=' && cmd->argv[k][j] == '=')
		{
			new_value = ft_strdup(cmd->argv[k]);
			if (!new_value)
				return (ft_putendl_fd("malloc failes", 2), true);
			free(shell->env[i]);
			shell->env[i] = new_value;
			return (true);
		}
		i++;
	}
	return (false);
}

void	free_double(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str && tab_str[i])
	{
		free(tab_str[i]);
		i++;
	}
	free(tab_str);
}

int	ft_strlenlen(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		i++;
	return (i);
}

void	wait_and_sig(pid_t pid, t_shell *shell)
{
	signal(SIGINT, sigchild);
	signal(SIGQUIT, sigquit_handler2);
	waitpid(pid, &shell->raw_statuts, 0);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
