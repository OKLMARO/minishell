/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:34:17 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/29 17:23:41 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_shell	*shell;

	((void) argv, (void) argc);
	shell = make_shell();
	if (!shell)
		return (ft_putstr_fd("MALLOC SHELL STRUCT ERROR", 2), 1);
	(signal(SIGQUIT, SIG_IGN), signal(SIGINT, sigint_handler));
	if (copy_env_in_shell(shell, env) == false)
		return (free(shell), ft_putstr_fd("ENV COPY ERROR", 2), 1);
	while (1)
	{
		input = readline("minishell $>");
		if (!input)
			break ;
		if (input[0])
		{
			add_history(input);
			shell->token = lexer(input);
			shell->cmd = parser(shell->token, 0);
			(expand_varialbes(shell->cmd, shell, 0), exec_shell(shell), free(input));
			(ft_cmddestroy(&shell->cmd), ft_tokendestroy(&shell->token));
		}
	}
	return (rl_clear_history(), delete_shell(shell), 0);
}
