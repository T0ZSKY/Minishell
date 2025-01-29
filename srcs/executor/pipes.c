/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:10:07 by taomalbe          #+#    #+#             */
/*   Updated: 2025/01/29 17:30:01 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_cmd_test(char *cmd, char **envp)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		perror("ft_split");
		exit(1);
	}
	path = find_command_path(args[0]);
	if (!path)
	{
		perror(args[0]);
		ft_free_tab(args);
		exit(1);
	}
	execve(path, args, envp);
	perror("execve");
	free(path);
	ft_free_tab(args);
	exit(1);
}

void	exec_pipes(char **command, char **envp)
{
	int		i;
	int		fd[2];
	int		prev_pipe;
	pid_t	pid;

	i = 0;
	prev_pipe = -1;
	while (command[i])
	{
		if (command[i + 1])
		{
			if (pipe(fd) == -1)
				return (perror("pipes"));
		}
		pid = fork();
		if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (command[i + 1])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			if (ft_strcmp(command[i], "echo") == 0)
				ft_echo(command);
			else
				ft_cmd_test(command[i], envp);
		}
		else
		{
			if (prev_pipe != -1)
				close(prev_pipe);
			if (command[i + 1])
				close(fd[1]);
			prev_pipe = fd[0];
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}
