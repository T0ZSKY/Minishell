/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:10:07 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/13 17:29:14 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	exec_child_3(t_pipe *pipes, t_shell *shell)
{
	char	*new;

	if (is_complex(shell->cmd) && !ft_strnstr(shell->cmd, "<<",
			ft_strlen(shell->cmd)))
	{
		redirections(shell->cmd);
		if (is_custom_cmd(shell->cmd))
			ft_custom_cmd_args(shell->cmd, shell);
		else
			ft_cmd_test(shell->cmd, pipes->envp);
		exit(0);
	}
	else if (is_custom_cmd(shell->cmd))
	{
		if (ft_custom_cmd_args(shell->cmd, shell) == 1)
		{
			printf("command not find : %s\n", shell->tab[0]);
			exit (127);
		}
		exit(0);
	}
	new = redir_space(shell->cmd);
	free(shell->cmd);
	ft_cmd_test(new, pipes->envp);
	exit(1);
}

void	exec_child_2(int prev_pipe, int fd[2], t_shell *shell, t_pipe *pipes)
{
	if (pipes->hdoc != -1)
	{
		dup2(pipes->hdoc, STDIN_FILENO);
		close(pipes->hdoc);
	}
	else if (prev_pipe != -1)
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
	exec_child_3(pipes, shell);
}

void	exec_child(int prev_pipe, int fd[2], t_pipe *pipes, t_shell *shell)
{
	int		i;
	char	**split_cmd;

	i = 0;
	pipes->hdoc = -1;
	if (is_complex(shell->cmd) && ft_strnstr(shell->cmd, "<<",
			ft_strlen(shell->cmd)))
	{
		split_cmd = ft_split_fou(shell->cmd);
		while (split_cmd[i + 1])
			i++;
		pipes->hdoc = heredoc(split_cmd[i]);
		ft_free_tab(split_cmd);
	}
	exec_child_2(prev_pipe, fd, shell, pipes);
}

void	exec_core(char **command, int i, t_pipe *pipes, t_shell *shell)
{
	if (pipes->pid == -1)
		return (perror("fork"));
	if (pipes->pid == 0)
	{
		shell->cmd = command[i];
		exec_child(pipes->prev_pipe, pipes->fd, pipes, shell);
	}
	pipes->pids[i] = pipes->pid;
	if (pipes->prev_pipe != -1)
		close(pipes->prev_pipe);
	if (command[i + 1] != NULL)
		close(pipes->fd[1]);
	pipes->prev_pipe = pipes->fd[0];
}

void	exec_pipes(char **command, char **envp, t_shell *shell)
{
	int		i;
	int		status;
	t_pipe	pipes;

	i = 0;
	status = 0;
	pipes.prev_pipe = -1;
	while (i < 1024)
		pipes.pids[i++] = 0;
	i = 0;
	while (command[i])
	{
		pipes.fd[0] = -1;
		pipes.fd[1] = -1;
		if (command[i + 1] != NULL && pipe(pipes.fd) == -1)
			return (perror("pipe"));
		pipes.envp = envp;
		pipes.pid = fork();
		exec_core(command, i, &pipes, shell);
		i++;
	}
	i = 0;
	while (i < 1024 && pipes.pids[i])
	{
		waitpid(pipes.pids[i], &status, 0);
		i++;
	}
}
