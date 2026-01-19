/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:34:17 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/19 14:11:39 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	while ((input = readline("minishell $>")))
		exec_shell(expand_varialbes(parser(lexer(input), 0), env), env);
}
