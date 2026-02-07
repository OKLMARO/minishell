/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:52:13 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/07 14:49:02 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sv;

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
	waitpid(pid, &shell->raw_statuts, 0);
	signal(SIGINT, sigint_handler);
}
