/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:10:24 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:16:32 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_cmd(char **tab, char **envp)
{
	pid_t pid;
	int status;
	char *cmd_path;
	char **args_copy = NULL;
	int i = 0;

	while (tab[i])
		i++;
	args_copy = malloc(sizeof(char *) * (i + 1));
	if (!args_copy)
		return;

	i = 0;
	while (tab[i]) {
		args_copy[i] = ft_strdup(tab[i]);
		if (!args_copy[i]) {
			ft_free_tab(args_copy);
			return;
		}
		i++;
	}
	args_copy[i] = NULL;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		ft_free_tab(args_copy);
		return;
	}

	if (pid == 0) {
		cmd_path = find_command_path(args_copy[0]);
		if (!cmd_path) {
			write(2, args_copy[0], strlen(args_copy[0]));
			write(2, ": command not found\n", 20);
			ft_free_tab(args_copy);
			exit(127);
		}

		if (execve(cmd_path, args_copy, envp) == -1) {
			perror("execve");
			free(cmd_path);
			ft_free_tab(args_copy);
			exit(126);
		}
	} else {
		ft_free_tab(args_copy);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
}
