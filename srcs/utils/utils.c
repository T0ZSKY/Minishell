/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:02 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/13 17:26:15 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		i;
	int		j;

	full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	i = 0;
	while (dir[i])
	{
		full_path[i] = dir[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	j = 0;
	while (cmd[j])
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

char	*redir_space(char *cmd)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc((ft_strlen(cmd) + 3) * sizeof(char));
	if (!new)
		return (NULL);
	while (cmd[j])
	{
		if (cmd[j] == '<' || cmd[j] == '>')
		{
			new[i++] = ' ';
			new[i++] = cmd[j];
			j++;
			if (cmd[j] == '<' || cmd[j] == '>')
			{
				new[i++] = cmd[j];
				new[i] = ' ';
				i++;
				j++;
			}
		}
		else
			new[i++] = cmd[j++];
	}
	new[i] = '\0';
	return (new);
}
