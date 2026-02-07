/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:34:17 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/07 14:32:30 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	routine(t_shell *shell, char *input)
{
	if (input[0])
	{
		add_history(input);
		shell->token = lexer(input);
		if (shell->token)
		{
			shell->cmd = parser(shell->token, 0, NULL);
			if (shell->cmd)
			{
				(expand_varialbes(shell->cmd, shell, 0));
				do_heredoc(shell, 0);
				(exec_shell(shell), free(input));
			}
		}
		if (shell->cmd)
			ft_cmddestroy(&shell->cmd);
		if (shell->token)
			ft_tokendestroy(&shell->token);
		g_sv = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_shell	*shell;

	((void) argv, (void) argc);
	(signal(SIGQUIT, SIG_IGN), signal(SIGINT, sigint_handler));
	shell = make_shell();
	if (!shell)
		return (ft_putstr_fd("MALLOC SHELL STRUCT ERROR", 2), 1);
	if (copy_env_in_shell(shell, env) == false)
		return (free(shell), ft_putendl_fd("ENV COPY ERROR", 2), 1);
	while (1)
	{
		input = readline("minishell $>");
		if (!input)
			break ;
		routine(shell, input);
		if (shell->cmd)
			ft_cmddestroy(&shell->cmd);
		if (shell->token)
			ft_tokendestroy(&shell->token);
	}
	return (rl_clear_history(), delete_shell(shell, NULL), 0);
}
