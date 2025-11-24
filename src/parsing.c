/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:46:30 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/24 14:20:51 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer(char *input)
{
	int		i;
	t_token	*list;
	char	buffer[4096];
	int		i_buffer;

	i = 0;
	i_buffer = 0;
	while (input[i])
	{
		if (input[i + 1] && input[i] == '<' && input[i + 1] == '<')
		{
			lexer_heredoc();
			i++;
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '<')
		{
			lexer_redirect_in(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i + 1] && input[i] == '>' && input[i + 1] == '>')
		{
			output_append();
			i++;
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '>')
		{
			lexer_redirect_out(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '|')
		{
			lexer_pipe(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '$')
		{
			lexer_env_var(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '\'')
		{
			lexer_single_quote(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == '"')
		{
			lexer_double_quote(ft_strdup(&input[i]));
			if (i_buffer != 0)
				lexer_word();
			i_buffer = 0;
		}
		else if (input[i] == ' ')
		{
			if (i_buffer != 0)
				lexer_word();
		}
		else
		{
			buffer[i_buffer] = input[i];
			i_buffer++;
		}
		i++;
	}
	return (list);
}

void	parsing(char **input)
{

