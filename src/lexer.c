/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:40:21 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/17 12:01:09 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int init_token(t_list **list)
{
	ft_lstadd_front(list, ft_lstnew("<"));
	ft_lstadd_front(list, ft_lstnew(">"));
	ft_lstadd_front(list, ft_lstnew("<<"));
	ft_lstadd_front(list, ft_lstnew(">>"));
	ft_lstadd_front(list, ft_lstnew("|"));
	ft_lstadd_front(list, ft_lstnew("$"));
	ft_lstadd_front(list, ft_lstnew("\""));
	ft_lstadd_front(list, ft_lstnew("'"));
	return (0);
}

char	*find_first_adr(char *res[])
{
	char	*min;
	int		i;

	i = 0;
	min = NULL;
	while (res[i])
	{
		if (min == NULL || min > res[i])
		{
			min = res[i];
			i++;
		}
	}
	return (min);
}

char	*is_token(t_list *list, char *token)
{
	char	*res[ft_lstsize(list)];
	t_list	*temp;
	int		i;

	temp = list;
	i = 0;
	while (temp)
	{
		if (ft_strnstr(token, temp->content, 3))
		{
			res[i] = ft_strnstr(token, temp->content, 3);
			i++;
		}
		temp = temp->next;
	}
	if (i == 0)
		return (NULL);
	if (i == 1)
		return (res[0]);
	return (find_first_adr(res));
}
