/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:35:54 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/05 15:59:19 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

t_shell	*init_shell(char **envp) //IMPORTANT j'appelle dans le main pour faire la copie de notre envp
{
	t_shell	*shell;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = malloc(sizeof(char *) * (count + 1));
	if (!shell->envp)
	{
		free(shell);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[count] = NULL;
	return (shell);
}

static char	**ft_replace_env_var(char **envp, char *var)
{
	int		i;
	size_t	len;

	len = ft_strchr(var, '=') - var + 1;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			return (envp);
		}
		i++;
	}
	return (NULL);
}

char	**ft_add_env_var(char **envp, char *var)
{
	char	**new_env;
	int		i;
	int		count;

	count = 0;
	while (envp[count])
		count++;
	if (ft_replace_env_var(envp, var))
		return (envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	return (new_env);
}

void	ft_print_env_sorted(char **envp)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	sorted_env = ft_copy_env(envp, count);
	if (!sorted_env)
		return ;
	ft_sort_env(sorted_env, count);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		free(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}

void	ft_export(char **tab, t_shell *shell)
{
	int	i;

	if (!tab[1])
	{
		ft_print_env_sorted(shell->envp);
		return ;
	}
	i = 1;
	while (tab[i])
	{
		shell->envp = ft_add_env_var(shell->envp, tab[i]);
		i++;
	}
}
