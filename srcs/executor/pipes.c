/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:10:07 by taomalbe          #+#    #+#             */
/*   Updated: 2025/01/28 15:12:33 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	exec_commands(char *cmd, char **envp)
{
	char	**split;

	split = ft_split(cmd, ' ');
	execve(split[0], split, envp);
	perror("execve");
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
			ft_cmd(command + i, envp);
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
