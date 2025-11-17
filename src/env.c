/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:49:51 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/17 12:00:38 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_user_dir(char **env)
{
	int		i;
	char	*user_dir;

	i = 0;
	user_dir = NULL;
	while (env[i])
	{
		if (ft_strncmp("USER_ZDOTDIR=", env[i], 13) == 0)
		{
			user_dir = ft_strdup(env[i] + 13);
			if (!user_dir)
				return (NULL);
		}
		i++;
	}
	return (user_dir);
}

char	**get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
		i++;
	}
	return (path);
}
