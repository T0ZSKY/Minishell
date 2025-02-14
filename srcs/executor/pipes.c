/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:10:07 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/14 20:58:21 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	handle_heredoc(char *cmd, int *heredoc_fd)
{
	char	**split_cmd;
	int		i;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	while (split_cmd[i] && ft_strcmp(split_cmd[i], "<<"))
		i++;
	*heredoc_fd = heredoc(split_cmd[i + 1]);
	ft_free_tab(split_cmd);
}

void	setup_redirections(int prev_pipe, int fd[2], int heredoc_fd)
{
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
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
}

void	exec_child(char *cmd, int prev_pipe, int fd[2], t_shell *shell)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	if (is_complex(cmd) && ft_strnstr(cmd, "<<", ft_strlen(cmd)))
		handle_heredoc(cmd, &heredoc_fd);
	setup_redirections(prev_pipe, fd, heredoc_fd);
	if (is_complex(cmd) && !ft_strnstr(cmd, "<<", ft_strlen(cmd)))
	{
		cmd = redirections(cmd);
		if (!cmd)
			exit(1);
	}
	if (is_custom_cmd(cmd))
	{
		if (ft_custom_cmd_args(cmd, shell) == 1)
		{
			printf("command not found: %s\n", shell->tab[0]);
			exit(127);
		}
		exit(0);
	}
	ft_cmd_test(cmd, shell->envp);
	exit(1);
}

pid_t	spawn_child(char *cmd, int prev_pipe, int fd[2], t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_child(cmd, prev_pipe, fd, shell);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (fd[1] != -1)
		close(fd[1]);
	return (pid);
}

void	exec_pipes(char **command, t_shell *shell)
{
	int		i;
	int		fd[2];
	int		prev_pipe;
	pid_t	pids[1024];
	int		status;

	i = 0;
	prev_pipe = -1;
	while (command[i])
	{
		fd[0] = -1;
		fd[1] = -1;
		if (command[i + 1] && pipe(fd) == -1)
			return (perror("pipe"));
		pids[i] = spawn_child(command[i], prev_pipe, fd, shell);
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
