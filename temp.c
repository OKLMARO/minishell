else if (args[i] && ft_strncmp(args[i], "pwd", 4) == 0)
				builtin_pwd();
			else if (args[i] && ft_strncmp(args[i], "cd", 3) == 0)
			{
				if (builtin_cd(args, env) == -1)
					return (1);
			}
			else if (args[i] && ft_strncmp(args[i], "echo", 5) == 0)
				builtin_echo(args);
			else if (args[i])
			{
				pid = fork();
				if (pid == 0)
				{
					if (!make_storage(&cmd, input, &all_cmd, path))
					{
						signal(SIGINT, SIG_DFL);
						signal(SIGQUIT, SIG_DFL);
						if (execve(all_cmd, cmd, env) == -1)
						{
							ft_putstr_fd("exec error\n", 2);
							return (1);
						}
					}
				}
				else if (pid > 0)
				{
					signal(SIGQUIT, sigquit_handler2);
					signal(SIGINT, sigint_handler2);
					waitpid(pid, NULL, 0);
					signal(SIGQUIT, SIG_IGN);
					signal(SIGINT, sigint_handler);
				}
				else
				{
					ft_putstr_fd("fork error", 2);
					return (1);
				}
			}