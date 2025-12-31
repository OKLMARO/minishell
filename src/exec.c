/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:46:24 by oamairi           #+#    #+#             */
/*   Updated: 2025/12/31 12:41:54 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_simple(t_cmd *cmd)
{
	
}

void	exec_shell(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (apply_redirection(cmd) == -1)
		return (my_exit(cmd, NULL, "redirection error"));
	if (!cmd->next)
		simple_exec(cmd);
	else if (!cmd->next->next)
		pipex(cmd);
	else
		multi_exec(cmd);
}
