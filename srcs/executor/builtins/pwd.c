/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:35:45 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 00:40:03 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

static char	*get_current_directory(void)
{
	char	*cwd;
	size_t	size;

	size = 1024;
	cwd = malloc(size);
	if (!cwd)
	{
		write(2, "Error: Memory allocation failed\n", 32);
		return (NULL);
	}
	while (!getcwd(cwd, size))
	{
		free(cwd);
		size *= 2;
		cwd = malloc(size);
		if (!cwd)
		{
			write(2, "Error: Memory allocation failed\n", 32);
			return (NULL);
		}
	}
	return (cwd);
}

void	ft_pwd(char **tab)
{
	char	*cwd;

	if (tab && tab[0] && !tab[1])
	{
		cwd = get_current_directory();
		if (cwd)
		{
			write(1, cwd, strlen(cwd));
			write(1, "\n", 1);
			free(cwd);
		}
	}
	else
	{
		write(2, "Error: Invalid arguments for 'pwd'\n", 35);
	}
}
