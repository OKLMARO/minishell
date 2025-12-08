/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:52:29 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/08 16:07:55 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_argv_to_cmd(t_cmd *cmd, char *argv)
{
	int		count;
	char	**new_argv;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char*) * (count + 2));
	if (!new_argv)
		return;
	count = 0;
	while (cmd->argv && cmd->argv[count])
	{
		new_argv[count] = cmd->argv[count];
		count++;
	}
	new_argv[count] = ft_strdup(argv);
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

t_cmd	*parser(t_token *token)
{
	t_token	*temp;
	t_cmd	*new;

	temp = token;
	while (temp->next != PIPE || temp)
	{
		new = ft_cmdnew();
		if (!new)
			return (NULL);
		if (temp->type == WORD)
			add_argv_to_cmd(new, temp->content);
		
	}
}
