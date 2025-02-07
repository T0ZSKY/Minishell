/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:36:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/06 19:24:58 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

//sacre here_doc pas gentil
int heredoc(char *limiter)
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


void	redirections(char **command)
{
	int	i;
	int	fd;

	i = 0;
	while (command[i + 1])
	{
		if (ft_strcmp(command[i], ">") == 0)
		{
			fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (perror(command[i + 1]), exit(1));
			dup2(fd, STDOUT_FILENO);
			close(fd);
			command[i] = NULL;
		}
		else if (ft_strcmp(command[i], ">>") == 0)
		{
			fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (perror(command[i + 1]), exit(1));
			dup2(fd, STDOUT_FILENO);
			close(fd);
			command[i] = NULL;
		}
		else if (ft_strcmp(command[i], "<") == 0)
		{
			fd = open(command[i + 1], O_RDONLY);
			if (fd == -1)
				return (perror(command[i + 1]), exit(1));
			dup2(fd, STDIN_FILENO);
			close(fd);
			command[i] = NULL;
		}
		else if (ft_strcmp(command[i], "<<") == 0)
		{
			fd = heredoc(command[i + 1]);
			if (fd == -1)
				return (perror("heredoc"), exit(1));
			dup2(fd, STDIN_FILENO);
			close(fd);
			command[i] = NULL;
		}
		i++;
	}
}
