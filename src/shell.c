/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:03:07 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/24 18:02:40 by oamairi          ###   ########.fr       */
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
	temp->exit_satuts = LONG_MIN;
	return (temp);
}


