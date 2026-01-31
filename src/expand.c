/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:30:35 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/31 11:41:04 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_variables(char *argv, char **env)
{
	int		i;
	char	*variable;

	i = 0;
	variable = NULL;
	while (env[i])
	{
		if (ft_strncmp(argv, env[i], ft_strlen(argv)) == 0
			&& env[i][ft_strlen(argv)] == '=')
		{
			variable = ft_strdup(env[i] + ft_strlen(argv) + 1);
			break ;
		}
		i++;
	}
	if (!variable)
		return (ft_strdup(""));
	return (variable);
}

char	*get_exit_status(t_shell *shell)
{
	char	*temp;

	if (g_sv == 130)
	{
		temp = ft_itoa(130);
		g_sv = 0;
	}
	else
		temp = ft_itoa(shell->exit_status);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*expand_varialbes(t_cmd *cmd_list, t_shell *shell, int i)
{
	t_cmd	*temp;
	char	*value;

	temp = cmd_list;
	while (temp)
	{
		i = 0;
		while (temp->argv && temp->argv[i])
		{
			if (temp->argv[i][0] == '$' && temp->quote[i] != 1)
			{
				if (temp->argv[i][1] == '?' && !temp->argv[i][2])
					value = get_exit_status(shell);
				else
					value = get_variables(temp->argv[i] + 1, shell->env);
				if (!value)
					return (NULL);
				free(temp->argv[i]);
				temp->argv[i] = value;
			}
			i++;
		}
		temp = temp->next;
	}
	return (NULL);
}
