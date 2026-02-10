/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:46:38 by oamairi           #+#    #+#             */
/*   Updated: 2026/02/10 11:16:10 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	simple_exec_no_path(t_shell *shell, t_cmd *cmd, char **path)
{
	if (access(cmd->argv[0], F_OK) == 0)
	{
		if (access(cmd->argv[0], X_OK) == -1)
			(perror(cmd->argv[0]), delete_shell(shell, path), exit(126));
		execve(cmd->argv[0], cmd->argv, shell->env);
		ft_putstr_fd("EXEC ERROR\n", 2);
		(delete_shell(shell, path), exit(127));
	}
	ft_putstr_fd("COMMAND NOT FOUND\n", 2);
	(delete_shell(shell, path), exit(127));
}

char	*valid_command(char *cmd, char **path)
{
	char	*valid_cmd;
	char	*temp;
	int		i;

	i = 0;
	valid_cmd = ft_strjoin("/", cmd);
	if (!valid_cmd)
		return (NULL);
	while (path && path[i])
	{
		temp = ft_strjoin(path[i], valid_cmd);
		if (!temp)
			return (free(valid_cmd), NULL);
		if (access(temp, F_OK) == 0)
			return (free(valid_cmd), temp);
		free(temp);
		i++;
	}
	return (free(valid_cmd), NULL);
}

int	make_storage(char ***cmd, char *argv, char **all_cmd, char **path)
{
	*cmd = ft_split(argv, ' ');
	if (!*cmd)
		return (perror("Malloc crash"), 1);
	*all_cmd = valid_command(*cmd[0], path);
	if (!*all_cmd)
		return (perror("Commande introuvable ou non executable"), 1);
	return (0);
}

void	get_clean_status(t_shell *shell)
{
	if (WIFEXITED(shell->raw_statuts))
		shell->exit_status = WEXITSTATUS(shell->raw_statuts);
	else if (WIFSIGNALED(shell->raw_statuts))
		shell->exit_status = WTERMSIG(shell->raw_statuts) + 128;
}
