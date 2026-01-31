/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:44:37 by oamairi           #+#    #+#             */
/*   Updated: 2026/01/31 20:36:36 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	builtin_parsing(t_shell *shell, t_cmd *cmd, char **path)
{
	if (cmd && cmd->argv)
	{
		if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
			return (shell->exit_status = builtin_pwd(cmd), true);
		else if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
			return (shell->exit_status = builtin_echo(cmd), true);
		else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
			return (shell->exit_status = builtin_cd(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
			return (shell->exit_status = builtin_env(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
			return (shell->exit_status = builtin_export(cmd, shell, 0), true);
		else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
			return (shell->exit_status = builtin_unset(cmd, shell), true);
		else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
			return (shell->exit_status = builtin_exit(cmd, shell, path), true);
		return (false);
	}
	return (false);
}
bool	builtin_exec(t_shell *shell, t_cmd *cmd, char **path)
{
	int		std_in;
	int		std_out;
	bool	is_builtin;
	std_in = dup(0);
	std_out = dup(1);
	if (std_in == -1 || std_out == -1)
		return (ft_putendl_fd("dup error", 2), false);
	if (apply_redirection(cmd) == false)
		return (false);
	is_builtin = builtin_parsing(shell, cmd, path);
	if (dup2(std_in, 0) == -1 || dup2(std_out, 1) == -1)
		return (ft_putendl_fd("dup2 error", 2), false);
	close(std_in);
	close(std_out);
	return (is_builtin);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell, char **path)
{
	int	exit_value;

	if (cmd->argv[1])
	{
		if (cmd->argv[2])
			return (ft_putendl_fd("too many arg", 2), 1);
		exit_value = ft_atoi(cmd->argv[1]);
		free_double(path);
		delete_shell(shell);
		exit(exit_value);
	}
	free_double(path);
	delete_shell(shell);
	exit(0);
	return (0);
}

int	builtin_pwd(t_cmd *cmd)
{
	char	cwd[4096];

	if (cmd->argv[1])
		return (ft_putstr_fd("too many arg\n", 2), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_putendl_fd(cwd, 1), 0);
	else
		return (ft_putstr_fd("pwd error\n", 2), 1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->argv[i] && ft_strncmp(cmd->argv[i], "-n",
			ft_strlen(cmd->argv[i])) == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (cmd->argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putendl_fd("", 1);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*usr_home;

	if (!cmd->argv[1])
	{
		usr_home = get_user_dir(shell->env);
		if (!usr_home)
			return (ft_putendl_fd("HOME ERROR", 2), 1);
		if (chdir(usr_home) == -1)
			return (free(usr_home), ft_putstr_fd("CD ERROR\n", 2), 1);
		return (free(usr_home), 0);
	}
	if (chdir(cmd->argv[1]) == -1)
		return (ft_putstr_fd("CD ERROR\n", 2), 1);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (cmd->argv[1])
		return (127);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
	return (0);
}

int	ft_strlenlen(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		i++;
	return (i);
}

bool	add_env(t_cmd *cmd, t_shell *shell)
{
	int		k;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (ft_strlenlen(shell->env) + 2));
	if (!new_env)
		return (ft_putendl_fd("Malloc error", 2), false);
	k = 0;
	while (shell->env && shell->env[k])
	{
		new_env[k] = ft_strdup(shell->env[k]);
		if (!new_env[k])
			return (free_double(new_env), perror("Malloc error"), false);
		k++;
	}
	new_env[k] = ft_strdup(cmd->argv[1]);
	new_env[k + 1] = NULL;
	free_double(shell->env);
	shell->env = new_env;
	return (true);
}

int	add_to_env(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		j;

	i = 1;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '=')
			return (ft_putendl_fd("need a valid identifier", 2), 1);
		j = 1;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == '=' && cmd->argv[i][j + 1])
			{
				if (add_env(cmd, shell) == false)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell, int i)
{
	char	*temp;

	if (!cmd->argv[1])
	{
		i = 0;
		while (shell->env && shell->env[i] && shell->env[i + 1])
		{
			if (ft_strncmp(shell->env[i], shell->env[i + 1], LONG_MAX) > 0)
			{
				temp = shell->env[i];
				shell->env[i] = shell->env[i + 1];
				shell->env[i + 1] = temp;
				i = 0;
			}
			i++;
		}
		i = 0;
		while (shell->env && shell->env[i])
		{
			ft_putendl_fd(shell->env[i], 1);
			i++;
		}
		return (0);
	}
	return (add_to_env(cmd, shell));
}

void	remove_env(t_shell *shell, int j)
{
	int		i;
	int		k;
	char	**new_env;

	new_env = malloc(sizeof(char *) * ft_strlenlen(shell->env));
	if (!new_env)
		return ;
	i = 0;
	k = 0;
	while (shell->env[i])
	{
		if (i == j)
			i++;
		else
		{
			new_env[k] = ft_strdup(shell->env[i]);
			if (!new_env[k])
				return (free_double(new_env));
			i++;
			k++;
		}
	}
	new_env[k] = NULL;
	free_double(shell->env);
	shell->env = new_env;
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;

	if (!cmd->argv[1])
		return (ft_putendl_fd("not enough arg", 2), 1);
	i = 1;
	while (cmd->argv[i])
	{
		j = 0;
		while (shell->env[j])
		{
			if (ft_strncmp(cmd->argv[i], shell->env[j], ft_strlen(cmd->argv[i]))
				== 0 && shell->env[j][ft_strlen(cmd->argv[i])] == '=')
			{
				remove_env(shell, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
