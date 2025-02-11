/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:54 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/11 14:35:43 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	is_complex(char *input)
{
	if (ft_strstr(input, "|") || ft_strstr(input, ">")
		|| ft_strstr(input, ">>") || ft_strstr(input, "<")
		|| ft_strstr(input, "<<"))
		return (1);
	return (0);
}

char	*replace_pipes(char *cmd)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = (char *)malloc((ft_strlen(cmd) + 1) * sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		if (new_cmd[i] == '|')
			new_cmd[i] = ' ';
		i++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}

char	**skip_pipes(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			if (!args[i + 1])
				exit(1);
			while (args[i + 1])
			{
				free(args[i]);
				args[i] = ft_strdup(args[i + 1]);
				i++;
			}
		}
		i++;
	}
	return (args);
}

int	is_custom_cmd(char *s)
{
	if (ft_strstr(s, "echo") || ft_strstr(s, "cd") || ft_strstr(s, "pwd")
		|| ft_strstr(s, "export") || ft_strstr(s, "env") || ft_strstr(s, "exit")
		|| ft_strstr(s, "unset"))
		return (1);
	return (0);
}
