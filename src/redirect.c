/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:39:37 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/21 10:06:12 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	redirect_here_doc_utils(void)
{
	int	file;

	file = open("/tmp/.minishell_heredoc", O_RDONLY);
	if (file < 0)
		return (ft_putstr_fd("HEREDOC ERROR", 2), false);
	if (dup2(file, 0) == -1)
		return (close(file), ft_putstr_fd("HEREDOC ERROR", 2), false);
	return (close(file), true);
}

bool	redirect_here_doc(t_redirect *redirect)
{
	int		file;
	char	*input;
	int		len_file;
	char	*temp_file;

	temp_file = "/tmp/.minishell_heredoc";
	len_file = ft_strlen(redirect->file);
	file = open(temp_file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (file < 0)
		return (ft_putstr_fd("HEREDOC ERROR", 2), false);
	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strncmp(redirect->file, input, len_file) == 0
				&& len_file == (int) ft_strlen(input)))
		{
			free(input);
			break ;
		}
		(ft_putstr_fd(input, file), ft_putchar_fd('\n', file), free(input));
	}
	close(file);
	return (redirect_here_doc_utils());
}

bool	redirect_append(t_redirect *redirect)
{
	int	file;

	file = open(redirect->file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (file < 0)
		return (ft_putstr_fd("FILE ERROR", 2), false);
	if (dup2(file, 1) == -1)
		return (close(file), ft_putstr_fd("REDIRECT ERROR", 2), false);
	return (close(file), true);
}

bool	redirect_in_out(t_redirect *redirect)
{
	int	file;

	if (redirect->type == REDIRECT_IN)
	{
		file = open(redirect->file, O_RDONLY);
		if (file < 0)
			return (ft_putstr_fd("FILE ERROR", 2), false);
		if (dup2(file, 0) == -1)
			return (close(file), ft_putstr_fd("REDIRECT ERROR", 2), false);
		return (close(file), true);
	}
	else if (redirect->type == REDIRECT_OUT)
	{
		file = open(redirect->file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (file < 0)
			return (ft_putstr_fd("FILE ERROR", 2), false);
		if (dup2(file, 1) == -1)
			return (close(file), ft_putstr_fd("REDIRECT ERROR", 2), false);
		return (close(file), true);
	}
	return (false);
}

bool	apply_redirection(t_cmd *cmd)
{
	t_redirect	*temp;

	temp = cmd->redirects;
	while (temp)
	{
		if (temp->type == REDIRECT_IN || temp->type == REDIRECT_OUT)
		{
			if (redirect_in_out(temp) == false)
				return (false);
		}
		else if (temp->type == APPEND)
		{
			if (redirect_append(temp) == false)
				return (false);
		}
		else if (temp->type == HERE_DOC)
		{
			if (redirect_here_doc(temp) == false)
				return (false);
		}
		else
			return (ft_putstr_fd("REDIRECT ERROR", 2), false);
		temp = temp->next;
	}
	return (true);
}
