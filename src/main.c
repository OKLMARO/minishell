/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:34:17 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/21 11:38:34 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*token;
	t_cmd	*cmd;

	(void) argv;
	(void) argc;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		input = readline("minishell $>");
		if (!input)
			break ;
		add_history(input);
		token = lexer(input);
		cmd = parser(token, 0);
		expand_varialbes(cmd, env);
		exec_shell(cmd, env);
		(ft_tokendestroy(&token), ft_cmddestroy(&cmd), free(input));
	}
	rl_clear_history();
	return (0);
}
