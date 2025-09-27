/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:06:09 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/24 16:33:33 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*temp;
	void	*data;

	if (!lst || !f || !del)
		return (0);
	lst_new = NULL;
	while (lst)
	{
		data = f(lst->content);
		temp = ft_lstnew(data);
		if (!temp)
		{
			ft_lstclear(&lst_new, del);
			del(data);
			return (0);
		}
		ft_lstadd_back(&lst_new, temp);
		lst = lst->next;
	}
	return (lst_new);
}
