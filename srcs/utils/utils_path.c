/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:15:25 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/11 14:18:30 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

static char	*allocate_and_copy(char *path, int start, int len)
{
	char	*dir;

	dir = malloc(len + 1);
	if (!dir)
		return (NULL);
	ft_strncpy(dir, &path[start], len);
	dir[len] = '\0';
	return (dir);
}

static int	count_dirs(char *path)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (path[i])
	{
		if (path[i] == ':')
			count++;
		i++;
	}
	return (count);
}

static int	get_len(char *path, int i)
{
	if (path[i] == ':')
		return (i);
	return (i + 1);
}

static char	**handle_split(char *path, int count)
{
	char	**dirs;
	int		i;
	int		j;
	int		start;
	int		len;

	dirs = malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':' || path[i + 1] == '\0')
		{
			len = get_len(path, i) - start;
			dirs[j] = allocate_and_copy(path, start, len);
			if (!dirs[j++])
				return (NULL);
			start = i + 1;
		}
		i++;
	}
	dirs[j] = NULL;
	return (dirs);
}

char	**split_path(char *path)
{
	int		count;

	count = count_dirs(path);
	return (handle_split(path, count));
}
