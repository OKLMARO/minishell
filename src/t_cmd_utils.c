/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:24:21 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/03 13:33:38 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redirectdestroy(t_redirect **lst)
{
	t_redirect	*temp;
	t_redirect	*temp_next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp && temp->next)
	{
		temp_next = temp->next;
		free(temp->file);
		free(temp);
		temp = temp_next;
	}
	free(temp->file);
	free(temp);
}

void	ft_cmddestroy(t_cmd **lst)
{
	t_cmd	*temp;
	t_cmd	*temp_next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp && temp->next)
	{
		temp_next = temp->next;
		free_double(temp->argv);
		ft_redirectdestroy(&temp->redirects);
		free(temp);
		temp = temp_next;
	}
	free_double(temp->argv);
	free(temp);
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!*lst)
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_redirectadd_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*temp;

	if (!*lst)
	{
		new->next = *lst;
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->argv = NULL;
	new->next = NULL;
	new->quote = NULL;
	new->redirects = NULL;
	return (new);
}
