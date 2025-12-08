/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:24:21 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/08 15:51:14 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cmdadd_front(t_cmd **lst, t_cmd *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!*lst)
	{
		ft_cmdadd_front(lst, new);
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

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->argv = NULL;
	new->next = NULL;
	new->redirects = NULL;
	return (new);
}
