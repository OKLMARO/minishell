/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:52:29 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/29 18:00:20 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_argv_to_cmd(t_cmd *cmd, t_token *lexer)
{
	int				count;
	t_quote_type	*quote;
	char			**new_argv;

	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	quote = malloc(sizeof(t_quote_type) * (count + 1));
	if (!quote)
		return (free(new_argv));
	count = 0;
	while (cmd->argv && cmd->argv[count])
	{
		new_argv[count] = cmd->argv[count];
		quote[count] = cmd->quote[count];
		count++;
	}
	new_argv[count] = ft_strdup(lexer->content);
	quote[count] = lexer->quote;
	new_argv[count + 1] = NULL;
	(free(cmd->argv), free(cmd->quote));
	cmd->argv = new_argv;
	cmd->quote = quote;
}

bool	add_redirect_to_cmd(t_token *temp, t_cmd *new)
{
	t_redirect	*new_redirect;

	if (!temp->next || temp->next->type != WORD)
		return (ft_putstr_fd("unexpected element\n", 2), false);
	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (false);
	new_redirect->type = temp->type;
	new_redirect->file = ft_strdup(temp->next->content);
	if (!new_redirect->file)
		return (false);
	new_redirect->next = NULL;
	ft_redirectadd_back(&new->redirects, new_redirect);
	return (true);
}

int	parser_compare(t_token *temp, t_cmd **cmd_list, t_cmd **new)
{
	if (temp->type == PIPE)
		return (ft_cmdadd_back(cmd_list, *new), 0);
	else if (temp->type == WORD)
		add_argv_to_cmd(*new, temp);
	else
	{
		if (add_redirect_to_cmd(temp, *new) == true)
			return (1);
		else
			return (-1);
	}
	return (2);
}

t_cmd	*parser(t_token *token, int result)
{
	t_token	*temp;
	t_cmd	*new;
	t_cmd	*cmd_list;

	temp = token;
	cmd_list = NULL;
	new = ft_cmdnew();
	if (!new)
		return (NULL);
	while (temp)
	{
		result = parser_compare(temp, &cmd_list, &new);
		if (result == -1)
			my_exit(&cmd_list, NULL, "unexpected element");
		else if (result == 0)
		{
			new = ft_cmdnew();
			if (!new)
				return (NULL);
		}
		else if (result == 1)
			temp = temp->next;
		temp = temp->next;
	}
	return (ft_cmdadd_back(&cmd_list, new), cmd_list);
}
