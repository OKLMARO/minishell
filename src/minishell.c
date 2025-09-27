/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:30:39 by oamairi           #+#    #+#             */
/*   Updated: 2025/09/27 16:03:41 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		sigation()
		while (1)
		{
			ft_putstr_fd("minishell>", 1);
		}
	}
	waitpid(pid, NULL, 0);
	return (0);
}
