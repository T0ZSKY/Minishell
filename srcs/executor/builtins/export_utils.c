/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:54:28 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 11:06:54 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char	**ft_copy_env(char **envp, int count)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(envp[i]);
		if (!sorted_env[i])
		{
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return (NULL);
		}
		i++;
	}
	sorted_env[count] = NULL;
	return (sorted_env);
}

void	ft_sort_env(char **sorted_env, int count)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
