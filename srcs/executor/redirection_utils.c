/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:00:49 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/20 14:22:27 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	handle_redirection(char *redir_type, char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0644);
	if (fd == -1)
		return (perror(file), -1);
	if (redir_type[0] == '>')
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	process_redirections(char **command, int *i)
{
	if (ft_strcmp(command[*i], ">") == 0)
		return (process_output_redirection(command, i));
	else if (ft_strcmp(command[*i], ">>") == 0)
		return (process_append_redirection(command, i));
	else if (ft_strcmp(command[*i], "<") == 0)
		return (process_input_redirection(command, i));
	else if (ft_strcmp(command[*i], "<<") == 0)
		return (process_heredoc_redirection(command, i));
	return (0);
}

int	process_heredoc_redirection(char **command, int *i)
{
	int	fd;

	fd = heredoc(command[*i + 1]);
	if (fd == -1)
	return (perror("heredoc"), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(command[*i]);
	command[*i] = ft_strdup(command[*i + 1]);
	return (0);
}

int	process_output_redirection(char **command, int *i)
{
	int	fd;

	fd = handle_redirection(">", command[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	free(command[*i]);
	command[*i] = ft_strdup(command[*i + 1]);
	return (0);
}

int	process_input_redirection(char **command, int *i)
{
	int	fd;

	fd = open(command[*i + 1], O_RDONLY);
	if (fd == -1)
		return (perror(command[*i + 1]), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(command[*i]);
	command[*i] = ft_strdup(command[*i + 1]);
	return (0);
}
