/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:36:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/14 21:15:03 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	*add_spaces_redirections(char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*new_cmd;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			len++;
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				i++;
		}
		len++;
		i++;
	}
	new_cmd = malloc(len + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (j > 0 && new_cmd[j - 1] != ' ')
				new_cmd[j++] = ' ';
			new_cmd[j++] = cmd[i++];
			if (cmd[i] == '>' || cmd[i] == '<')
				new_cmd[j++] = cmd[i++];
			if (cmd[i] && cmd[i] != ' ')
				new_cmd[j++] = ' ';
		}
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

int	heredoc(char *limiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(limiter, line) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

char	*redirections(char *cmd)
{
	int		i;
	int		fd;
	char	**command;
	char	*spaced_cmd;

	i = 0;
	spaced_cmd = add_spaces_redirections(cmd);
	if (!spaced_cmd)
		return (cmd);
	command = ft_split(spaced_cmd, ' ');
	while (command[i + 1])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(command[i + 1]), NULL);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			free(command[i]);
			command[i] = ft_strdup(command[i + 1]);
		}
		else if (ft_strcmp(command[i], ">>") == 0)
		{
			fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(command[i + 1]), NULL);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			free(command[i]);
			command[i] = ft_strdup(command[i + 1]);
		}
		else if (ft_strcmp(command[i], "<") == 0)
		{
			fd = open(command[i + 1], O_RDONLY);
			if (fd == -1)
				return (perror(command[i + 1]), NULL);
			dup2(fd, STDIN_FILENO);
			close(fd);
			free(command[i]);
			command[i] = ft_strdup(command[i + 1]);
		}
		else if (ft_strcmp(command[i], "<<") == 0)
		{
			fd = heredoc(command[i + 1]);
			if (fd == -1)
				return (perror("heredoc"), NULL);
			dup2(fd, STDIN_FILENO);
			close(fd);
			free(command[i]);
			command[i] = ft_strdup(command[i + 1]);
		}
		i++;
	}
	free(cmd);
	return (spaced_cmd);
}

void	null_complex(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (is_complex(redir[i]))
		{
			free(redir[i]);
			redir[i] = NULL;
			i++;
			while (redir[i])
				free(redir[i++]);
			break ;
		}
		i++;
	}
}
