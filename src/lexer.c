/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:40:21 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/03 16:42:48 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_word(t_token_type type, t_token **list, char *buffer)
{
	t_token	*new;

	new = ft_tokennew(type, ft_strdup(buffer));
	if (!new)
		return (NULL);
	ft_tokenadd_back(list, new);
	return (new);
}

void	make_lexer(t_token_type type, t_token **list, char *buffer)
{
	int	i;

	if (buffer[0] != '\0')
		lexer_word(WORD, list, buffer);
	ft_memset(buffer, '\0', 4096);
	if (type == HERE_DOC)
		(ft_memcpy(buffer, "<<", 3), lexer_word(HERE_DOC, list, buffer));
	else if (type == REDIRECT_IN)
		(ft_memcpy(buffer, "<", 2), lexer_word(REDIRECT_IN, list, buffer));
	else if (type == APPEND)
		(ft_memcpy(buffer, ">>", 3), lexer_word(APPEND, list, buffer));
	else if (type == REDIRECT_OUT)
		(ft_memcpy(buffer, ">", 2), lexer_word(REDIRECT_OUT, list, buffer));
	else if (type == PIPE)
		(ft_memcpy(buffer, "|", 2), lexer_word(PIPE, list, buffer));
	else if (type == DOLLAR)
		(ft_memcpy(buffer, "$", 2), lexer_word(DOLLAR, list, buffer));
	else if (type == SINGLE)
		(ft_memcpy(buffer, "'", 2), lexer_word(SINGLE, list, buffer));
	else if (type == DOUBLE)
		(ft_memcpy(buffer, "\"", 2), lexer_word(DOUBLE, list, buffer));
}

bool	lexer_compare(char *input, t_token **list, int *i, char *buffer)
{
	if (input[*i + 1] && input[*i] == '<' && input[*i + 1] == '<')
	{
		*i = *i + 1;
		return (make_lexer(HERE_DOC, list, buffer), true);
	}
	else if (input[*i] == '<')
		return (make_lexer(REDIRECT_IN, list, buffer), true);
	else if (input[*i + 1] && input[*i] == '>' && input[*i + 1] == '>')
	{
		*i = *i + 1;
		return (make_lexer(APPEND, list, buffer), true);
	}
	else if (input[*i] == '>')
		return (make_lexer(REDIRECT_OUT, list, buffer), true);
	else if (input[*i] == '|')
		return (make_lexer(PIPE, list, buffer), true);
	else if (input[*i] == '$')
		return (make_lexer(DOLLAR, list, buffer), true);
	else if (input[*i] == '\'')
		return (make_lexer(SINGLE, list, buffer), true);
	else if (input[*i] == '"')
		return (make_lexer(DOUBLE, list, buffer), true);
	else if (input[*i] == ' ')
		return (make_lexer(WORD, list, buffer), true);
	return (false);
}

void	add_to_buffer(char *buffer, int *i_buffer, char *input, int i)
{
	buffer[*i_buffer] = input[i];
	*i_buffer = *i_buffer + 1;
	buffer[*i_buffer] = '\0';
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
		ft_tokenadd_back(&list, ft_tokennew(WORD, ft_strdup(buffer)));
	return (free(buffer), list);
}
