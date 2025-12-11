/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:40:21 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/11 11:09:01 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_word(t_token_type type, t_token **list, char *buffer,
	t_quote_type quote)
{
	t_token	*new;

	new = ft_tokennew(type, ft_strdup(buffer), quote);
	if (!new)
		return (NULL);
	ft_tokenadd_back(list, new);
	return (new);
}

void	make_lexer(t_token_type type, t_token **list, char *buffer,
	t_quote_type quote)
{
	int	i;

	if (buffer[0] != '\0')
		lexer_word(WORD, list, buffer, NO_QUOTE);
	ft_memset(buffer, '\0', 4096);
	if (type == HERE_DOC)
		(ft_memcpy(buffer, "<<", 3), lexer_word(HERE_DOC, list, buffer,
				NO_QUOTE));
	else if (type == REDIRECT_IN)
		(ft_memcpy(buffer, "<", 2), lexer_word(REDIRECT_IN, list, buffer,
				NO_QUOTE));
	else if (type == APPEND)
		(ft_memcpy(buffer, ">>", 3), lexer_word(APPEND, list, buffer,
				NO_QUOTE));
	else if (type == REDIRECT_OUT)
		(ft_memcpy(buffer, ">", 2), lexer_word(REDIRECT_OUT, list, buffer,
				NO_QUOTE));
	else if (type == PIPE)
		(ft_memcpy(buffer, "|", 2), lexer_word(PIPE, list, buffer,
				NO_QUOTE));
}

bool	make_lexer_single_quote(char *input, t_token **list, int *i,
	char *buffer)
{
	int	i_buffer;

	if (buffer[0] != '\0')
		lexer_word(WORD, list, buffer, NO_QUOTE);
	ft_memset(buffer, '\0', 4096);
	i_buffer = 0;
	*i = *i + 1;
	while (input[*i] != '\'' && input[*i])
	{
		add_to_buffer(buffer, &i_buffer, input, *i);
		*i = *i + 1;
	}
	if (!input[*i])
		return (ft_putstr_fd("unexpected element\n", 2), false);
	return (lexer_word(WORD, list, buffer, SINGLE_QUOTE), true);
}

bool	make_lexer_double_quote(char *input, t_token **list, int *i,
	char *buffer)
{
	int	i_buffer;

	if (buffer[0] != '\0')
		lexer_word(WORD, list, buffer, NO_QUOTE);
	ft_memset(buffer, '\0', 4096);
	i_buffer = 0;
	*i = *i + 1;
	while (input[*i] != '"' && input[*i])
	{
		add_to_buffer(buffer, &i_buffer, input, *i);
		*i = *i + 1;
	}
	if (!input[*i])
		return (ft_putstr_fd("unexpected element\n", 2), false);
	return (lexer_word(WORD, list, buffer, DOUBLE_QUOTE), true);
}

t_token	*lexer(char *input)
{
	int		i;
	t_token	*list;
	char	*buffer;
	int		i_buffer;

	i = 0;
	i_buffer = 0;
	list = NULL;
	buffer = malloc(sizeof(char) * 4096);
	if (!buffer)
		return (NULL);
	ft_memset(buffer, '\0', 4096);
	while (input[i])
	{
		if (lexer_compare(input, &list, &i, buffer) == false)
			add_to_buffer(buffer, &i_buffer, input, i);
		else
			(ft_memset(buffer, '\0', 4096), i_buffer = 0);
		i++;
	}
	if (i_buffer > 0)
		ft_tokenadd_back(&list, ft_tokennew(WORD, ft_strdup(buffer), NO_QUOTE));
	return (free(buffer), list);
}
