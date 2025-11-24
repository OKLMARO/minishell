/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:46:30 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/24 11:19:11 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer(char **input)
{
	
}

void	parsing(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i + 1] && input[i] == '<' && input[i + 1] == '<')
			heredoc();
		else if (input[i] == '<')
			redirect_in();
		else if (input[i + 1] && input[i] == '>' && input[i + 1] == '>')
			output_append();
		else if (input[i] == '>')
			redirect_out();
		else if (input[i] == '|')
			pipex();
		else if (input[i] == '$')
			env_var();
		else if (input[i] == '\'')
			sing_quote();
		else if (input[i] == '"')
			double_quote();
		i++;
	}
}
