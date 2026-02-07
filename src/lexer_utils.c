/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:34:45 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/07 14:28:15 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_to_buffer(char *buffer, int *i_buffer, char *input, int i)
{
	buffer[*i_buffer] = input[i];
	*i_buffer = *i_buffer + 1;
	buffer[*i_buffer] = '\0';
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
	else if (input[*i] == '\'')
		return (make_lexer_single_quote(input, list, i, buffer), true);
	else if (input[*i] == '"')
		return (make_lexer_double_quote(input, list, i, buffer));
	else if (input[*i] == ' ')
		return (make_lexer(WORD, list, buffer), true);
	return (false);
}
