/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:54:11 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/01 23:55:34 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	g_sv = 130;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler2(int signo)
{
	(void)signo;
	g_sv = 130;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigquit_handler2(int signo)
{
	(void)signo;
	write(2, "Quit (core dumped)", 19);
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigchild(int signo)
{
	(void)signo;
	write(1, "\n", 1);
}
