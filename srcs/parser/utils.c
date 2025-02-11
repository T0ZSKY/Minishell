/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:54 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/11 16:42:29 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	charset_complex(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*uncomplex_input(char *input)
{
	int		i;
	int		flag;
	char	*c_input;

	i = 0;
	flag = 0;
	c_input = ft_strdup(input);
	while (c_input[i])
	{
		if (c_input[i] == '"' && flag == 1)
			break ;
		if (c_input[i] == '"' && flag == 0)
			flag = 1;
		if (flag == 1 && charset_complex(c_input[i]))
			c_input[i] = ' ';
		i++;
	}
	return (c_input);
}

int	is_complex(char *input)
{
	int		i;
	int		flag;
	char	*c_input;

	i = 0;
	flag = 0;
	c_input = ft_strdup(input);
	while (c_input[i])
	{
		if (c_input[i] == '"' && flag == 1)
			break ;
		if (c_input[i] == '"' && flag == 0)
			flag = 1;
		if (flag == 1 && charset_complex(c_input[i]))
			c_input[i] = ' ';
		i++;
	}
	if (ft_strstr(c_input, "|") || ft_strstr(c_input, ">")
		|| ft_strstr(c_input, ">>") || ft_strstr(c_input, "<")
		|| ft_strstr(c_input, "<<"))
		return (free(c_input), 1);
	return (free(c_input), 0);
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
