/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:50:10 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/01 22:25:10 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_exit(t_cmd **cmd, t_token **token, char *string)
{
	if (cmd && *cmd)
		ft_cmddestroy(cmd);
	if (token && *token)
		ft_tokendestroy(token);
	if (string)
		ft_putendl_fd(string, 2);
}

t_redirect	*ft_redirectnew(char *file, t_token_type type)
{
	t_redirect	*new;
	char		*temp_file;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	temp_file = ft_strdup(file);
	new->file = temp_file;
	new->next = NULL;
	new->type = type;
	return (new);
}

void	ft_tokendestroy(t_token **lst)
{
	t_token	*temp;
	t_token	*temp_next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp && temp->next)
	{
		temp_next = temp->next;
		free(temp->content);
		free(temp);
		temp = temp_next;
	}
	free(temp->content);
	free(temp);
	*lst = NULL;
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

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

t_token	*ft_tokennew(t_token_type type, void *s, t_quote_type quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = s;
	new->quote = quote;
	new->next = NULL;
	return (new);
}
