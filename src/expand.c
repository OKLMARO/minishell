/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:30:35 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/30 11:54:55 by oamairi          ###   ########.fr       */
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

char	*expand_varialbes(t_cmd *cmd_list, char **env)
{
	int		i;
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
				value = get_variables(temp->argv[i] + 1, env);
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
