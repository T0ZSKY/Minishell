/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:02 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:42:42 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char *join_path(char *dir, char *cmd)
{
	char *full_path;
	int i;
	int j;

	full_path = malloc(strlen(dir) + strlen(cmd) + 2);
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
//promis je la normerais mdr
char **split_path(char *path)
{
	char **dirs;
	int count;
	int i;
	int j;
	int start;

	count = 1;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}

	dirs = malloc(sizeof(char *) * (count + 1));
	if (!dirs)
		return (NULL);

	i = 0;
	j = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':' || path[i + 1] == '\0')
		{
			if (path[i] == ':')
			{
				dirs[j] = malloc(i - start + 1);
				if (!dirs[j])
					return (NULL);
				ft_strncpy(dirs[j], &path[start], i - start);
				dirs[j][i - start] = '\0';
				j++;
				start = i + 1;
			}
			else
			{
				dirs[j] = malloc(i - start + 2);
				if (!dirs[j])
					return (NULL);
				ft_strncpy(dirs[j], &path[start], i - start + 1);
				dirs[j][i - start + 1] = '\0';
				j++;
			}
		}
		i++;
	}
	dirs[j] = NULL;
	return (dirs);
}

