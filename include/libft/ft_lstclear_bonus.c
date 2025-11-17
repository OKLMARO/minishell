/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:22:09 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/24 16:02:38 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_next;

	if (!lst)
		return ;
	lst_next = *lst;
	while (lst_next)
	{
		lst_next = lst_next->next;
		ft_lstdelone(*lst, del);
		*lst = lst_next;
	}
}
