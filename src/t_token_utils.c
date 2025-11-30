/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:50:10 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/30 16:47:04 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!*lst)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token	*ft_tokennew(t_token_type type, void *s)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = s;
	new->next = NULL;
	return (new);
}
