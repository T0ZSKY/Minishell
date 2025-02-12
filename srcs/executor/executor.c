/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:10:24 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/12 02:54:15 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	**copy_arguments(char **tab)
{
	char	**args_copy;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	args_copy = malloc(sizeof(char *) * (i + 1));
	if (!args_copy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		args_copy[i] = ft_strdup(tab[i]);
		if (!args_copy[i])
		{
			ft_free_tab(args_copy);
			return (NULL);
		}
		i++;
	}
	args_copy[i] = NULL;
	return (args_copy);
}

void	execute_child(char **args_copy, char **envp)
{
	char	*cmd_path;

	cmd_path = find_command_path(args_copy[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", args_copy[0]);
		ft_free_tab(args_copy);
		exit(127);
	}
	if (execve(cmd_path, args_copy, envp) == -1)
	{
		perror("execve");
		free(cmd_path);
		ft_free_tab(args_copy);
		exit(126);
	}
	free(cmd_path);
}

void	check_path_exists(t_shell *shell, char **tab)
{
	int	i;
	int	path_found;

	i = 0;
	path_found = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
		{
			path_found = 1;
			break ;
		}
		i++;
	}
	if (!path_found)
	{
		printf("minishell: %s: No such file or directory\n", tab[0]);
		g_last_exit_status = 127;
	}
}

void	execute_command(char **args_copy, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_free_tab(args_copy);
		g_last_exit_status = 1;
		return ;
	}
	if (pid == 0)
		execute_child(args_copy, envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else
			g_last_exit_status = 1;
		ft_free_tab(args_copy);
	}
}

void	ft_cmd(char **tab, char **envp, t_shell *shell)
{
	char	**args_copy;

	g_last_exit_status = 0;
	check_path_exists(shell, tab);
	if (g_last_exit_status == 127)
		return ;
	args_copy = copy_arguments(tab);
	if (!args_copy)
		return ;
	execute_command(args_copy, envp);
}
