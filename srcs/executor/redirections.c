/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:36:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/04 16:08:42 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	heredoc(char	*limiter)
{
	int		fd[2];
	char	**line;

	if (pipe(fd) == -1)
		perror("pipe");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(limiter, line, ft_strlen(limiter)) == 0);
			exit(0);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
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
			fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); //make error check
			if (fd == -1)
				perror("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			command[i] = NULL;
		}
		else if (ft_strcmp(command[i], ">>") == 0)
        {
            fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); //make error check
			if (fd == -1)
				perror("open");
			dup2(fd, STDOUT_FILENO);
			close(fd);
			command[i] = NULL;
        }
		else if (ft_strcmp(command[i], "<") == 0)
        {
            fd = open(command[i + 1], O_RDONLY); //make error check
			if (fd == -1)
				perror("open");
			dup2(fd, STDIN_FILENO);
			close(fd);
			command[i] = NULL;
        }
		else if (ft_strcmp(command[i], "<<") == 0)
        {
            heredoc(command[i + 1]);
			command[i] = NULL;
        }
		i++;
	}
}
