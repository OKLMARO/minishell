/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:46:30 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/30 18:28:56 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_buffer(char buffer[4096])
{
	int	j;

	j = 0;
	while (j < 4096)
	{
		buffer[j] = '\0';
		j++;
	}
}

t_token	*lexer_compare(char *input, t_token **list, int *i, char buffer[4096])
{
	if (input[*i + 1] && input[*i] == '<' && input[*i + 1] == '<') /*ici je vais demander si il faut faire une fonction separer du reste*/
		return (lexer_word(WORD, list, buffer), lexer_word(HERE_DOC, list, buffer));
	else if (input[*i] == '<')
		return (lexer_word(REDIRECT_IN, list, buffer));
	else if (input[*i + 1] && input[*i] == '>' && input[*i + 1] == '>')
		return (lexer_word(APPEND, list, buffer));
	else if (input[*i] == '>')
		return (lexer_word(REDIRECT_OUT, list, buffer));
	else if (input[*i] == '|')
		return (lexer_word(PIPE, list, buffer));
	else if (input[*i] == '$')
		return (lexer_word(DOLLAR, list, buffer));
	else if (input[*i] == '\'')
		return (lexer_word(SINGLE, list, buffer));
	else if (input[*i] == '"')
		return (lexer_word(DOUBLE, list, buffer));
	else if (input[*i] == ' ')
		return (lexer_word(WORD, list, buffer));
	return (NULL);
}

t_token	*lexer_word(t_token_type type, t_token **list, char buffer[4096])
{
	t_token	*new;
	t_token	*old;

	old = ft_tokennew(WORD, buffer);
	if (!old)
		return (NULL);
	ft_tokenadd_back(&list, old);
	reset_buffer(buffer);
	new = ft_tokennew(type, buffer);
	if (!new)
		return (NULL);
	ft_tokenadd_back(&list, new);
	return (new);
}

t_token	*lexer(char *input)
{
	int		i;
	t_token	*list;
	char	buffer[4096];
	int		i_buffer;

	i = 0;
	i_buffer = 0;
	list = NULL;
	while (input[i])
	{
		if (lexer_compare(input, &list, &i, buffer) == NULL)
		{
			buffer[i_buffer] = input[i];
			i_buffer++;
			buffer[i_buffer] = '\0';
		}
		else
			(reset_buffer(buffer), i_buffer = 0);
		i++;
	}
	return (list);
}
