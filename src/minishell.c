/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:45:34 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/17 11:59:24 by oamairi          ###   ########.fr       */
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
	int	file;

	file = -1;
	if (open_redirect_in(args, i, &file, list) == -1)
		return (ft_putendl_fd("Redirect in error\n", 2), 1);
	dup2(file, 0);
	return (0);
}

int	redirect_out(char **args, int i, t_list *list)
{
	int	file;

	file = -1;
	if (open_redirect_out(args, i, &file, list) == -1)
		return (ft_putstr_fd("Redirect out error\n", 2), 1);
	dup2(file, 1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	//pid_t	pid;
	char	**args;
	char	**path;
	//char	**cmd;
	//char	*all_cmd;
	t_list	*token;
	int		i;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	token = malloc(sizeof(t_list));
	init_token(&token);
	path = get_path(env);
	if (!path)
		return (ft_putstr_fd("Env error", 2), 2);
	while ((input = readline("")))
	{
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strncmp(input, "exit", 15) == 0)
		{
			ft_putstr_fd("exit", 1);
			free(input);
			break;
		}
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		i = 0;
		while (args[i])
		{
			/*if (ft_strncmp(is_token(token, args[i]), "|", 3))
				pipex(...);*/
			if (ft_strncmp(args[i], "<", 1) == 0)
				redirect_in(args, i, token);
			if (ft_strncmp(args[i], ">", 1) == 0)
				redirect_out(args, i, token);
			/*else if (ft_strncmp(is_token(token, args[i]), "<<", 3))
				jsp(...);
			else if (ft_strncmp(is_token(token, args[i]), ">>", 3))
				redirect_out_append(...);*/
			i++;
		}
		free(input);
		free_double(args);
	}
	return (0);
}
