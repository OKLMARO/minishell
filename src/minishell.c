/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:45:34 by oamairi           #+#    #+#             */
/*   Updated: 2025/11/22 16:19:44 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*input;
	//pid_t	pid;
	char	**args;
	char	**path;
	//char	**cmd;
	//char	*all_cmd;
	t_list	*token;
	pid_t	fils;
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
	while ((input = readline("minishell $>")))
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
		fils = fork();
		if (fils == 0)
		{
			i = 0;
			while(args[i])
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
			exit(1);
		}
		waitpid(fils, NULL, 0);
		free(input);
		free_double(args);
	}
	return (0);
}
