/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:52:13 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/29 17:23:19 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_double(char **tab_str)
{
	int	i;

	i = 0;
	while (tab_str && tab_str[i])
	{
		free(tab_str[i]);
		i++;
	}
	free(tab_str);
}

void	sigint_handler(int signo)
{
	(void)signo;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler2(int signo)
{
	(void)signo;
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
