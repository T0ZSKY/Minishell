/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:10:07 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/06 15:49:24 by tomlimon         ###   ########.fr       */
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

void	exec_child(char *cmd, int prev_pipe, int fd[2], char **envp, t_shell *shell)
{
	char	**redir;

	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (fd[1] != -1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	if (is_custom_cmd(cmd))
		ft_custom_cmd_args(cmd, shell);
	else
		ft_cmd_test(cmd, envp);
	exit(1);
}

void	exec_pipes(char **command, char **envp, t_shell *shell)
{
	int		i;
	int		fd[2];
	int		prev_pipe;
	pid_t	pid;
	int		status;
	pid_t	pids[1024];

	i = 0;
	prev_pipe = -1;
	while (command[i])
	{
		fd[0] = -1;
		fd[1] = -1;
		if (command[i + 1] != NULL && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
			exec_child(command[i], prev_pipe, fd, envp, shell);
		pids[i] = pid;
		if (prev_pipe != -1)
			close(prev_pipe);
		if (command[i + 1] != NULL)
			close(fd[1]);
		prev_pipe = fd[0];
		i++;
	}
	i = 0;
	while (i < 1024 && pids[i])
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

