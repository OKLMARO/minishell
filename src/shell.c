/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:03:07 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/31 11:43:28 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*make_shell(void)
{
	t_shell	*temp;

	temp = malloc(sizeof(t_shell));
	if (!temp)
		return (NULL);
	temp->cmd = NULL;
	temp->token = NULL;
	temp->env = NULL;
	temp->exit_status = 0;
	temp->raw_statuts = 0;
	return (temp);
}

bool	copy_env_in_shell(t_shell *shell, char **env)
{
	char	**copy_env;
	int		len_env;

	len_env = 0;
	while (env[len_env])
		len_env++;
	copy_env = malloc(sizeof(char *) * (len_env + 1));
	if (!copy_env)
		return (false);
	len_env = 0;
	while (env[len_env])
	{
		copy_env[len_env] = ft_strdup(env[len_env]);
		if (!copy_env[len_env])
			return (free_double(copy_env), false);
		len_env++;
	}
	copy_env[len_env] = NULL;
	shell->env = copy_env;
	return (true);
}

void	delete_shell(t_shell *shell)
{
	if (shell->cmd)
		ft_cmddestroy(&shell->cmd);
	if (shell->token)
		ft_tokendestroy(&shell->token);
	free_double(shell->env);
	free(shell);
}
