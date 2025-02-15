/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:13:33 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/15 21:07:16 by tomlimon         ###   ########.fr       */
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
	if (is_complex(cmd))
		null_complex(args);
	free(cmd);
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

int	calculate_new_length(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (len > 0 && i > 0 && cmd[i - 1] != ' ')
				len++;
			len++;
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
			{
				len++;
				i++;
			}
			if (cmd[i + 1] && cmd[i + 1] != ' ')
				len++;
		}
		len++;
		i++;
	}
	return (len);
}

void	copy_with_spaces(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '>' || src[i] == '<')
		{
			if (j > 0 && dest[j - 1] != ' ')
				dest[j++] = ' ';
			dest[j++] = src[i++];
			if (src[i] == '>' || src[i] == '<')
				dest[j++] = src[i++];
			if (src[i] && src[i] != ' ')
				dest[j++] = ' ';
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}

int	process_append_redirection(char **command, int *i)
{
	int	fd;

	fd = handle_redirection(">>", command[*i + 1],
			O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		return (-1);
	free(command[*i]);
	command[*i] = ft_strdup(command[*i + 1]);
	return (0);
}
