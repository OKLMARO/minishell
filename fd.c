/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:19:59 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/22 15:57:29 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_redirect_out(char **args, int i, int *file, t_list *list)
{
	char	*token;
	char	*temp;

	token = is_token(list, args[i]);
	if (ft_strlen(token) == 1)
	{
		*file = open(args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (*file < 0)
			return (-1);
	}
	else
	{
		temp = ft_strdup(token + 1);
		if (!temp)
			return (-1);
		*file = open(temp, O_WRONLY | O_TRUNC);
		free(temp);
		if (*file < 0)
			return (-1);
	}
	return (*file);
}

int	open_redirect_in(char **args, int i, int *file, t_list *list)
{
	char	*token;
	char	*temp;

	token = is_token(list, args[i]);
	if (ft_strlen(token) == 1)
	{
		*file = open(args[i + 1], O_RDONLY);
		if (*file < 0)
			return (-1);
	}
	else
	{
		temp = ft_strdup(token + 1);
		if (!temp)
			return (-1);
		*file = open(temp, O_RDONLY);
		free(temp);
		if (*file < 0)
			return (-1);
	}
	return (*file);
}

int	redirect_in(char **args, int i, t_list *list)
{
	int		file;

	file = -1;
	if (open_redirect_in(args, i, &file, list) == -1)
		return (ft_putendl_fd("Redirect in error\n", 2), 1);
	dup2(file, 0);
	close(file);
	return (0);
}

int	redirect_out(char **args, int i, t_list *list)
{
	int		file;

	file = -1;
	if (open_redirect_out(args, i, &file, list) == -1)
		return (ft_putstr_fd("Redirect out error\n", 2), 1);
	dup2(file, 1);
	close(file);
	return (0);
}
