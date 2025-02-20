/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:36:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/20 14:46:03 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	*add_spaces_redirections(char *cmd)
{
	int		len;
	char	*new_cmd;

	len = calculate_new_length(cmd);
	new_cmd = malloc(len + 1);
	if (!new_cmd)
		return (NULL);
	copy_with_spaces(new_cmd, cmd);
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
	char	**command;
	char	*spaced_cmd;

	i = 0;
	spaced_cmd = add_spaces_redirections(cmd);
	if (!spaced_cmd)
		return (cmd);
	command = ft_split(spaced_cmd, ' ');
	while (command[i + 1])
	{
		if (process_redirections(command, &i) == -1)
		{
			ft_free_tab(command);
			free(cmd);
			return (NULL);
		}
		i++;
	}
	ft_free_tab(command);
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
