/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:42:54 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/11 17:31:08 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

static void	remove_env_var(char *var, t_shell *shell)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(var);
	while (shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], var, len) == 0)
		{
			free(shell->envp[j]);
			while (shell->envp[j + 1])
			{
				shell->envp[j] = shell->envp[j + 1];
				j++;
			}
			shell->envp[j] = NULL;
			break ;
		}
		j++;
	}
}

void	ft_unset(char **tab, t_shell *shell)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		remove_env_var(tab[i], shell);
		i++;
	}
}
