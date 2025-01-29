/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:42:54 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 17:37:59 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void ft_unset(char **tab, t_shell *shell)
{
	int i = 1;
	int j;
	int len;

	while (tab[i])
	{
		j = 0;
		len = ft_strlen(tab[i]);
		while (shell->envp[j])
		{
			if (ft_strncmp(shell->envp[j], tab[i], len) == 0)
			{
				free(shell->envp[j]);
				while (shell->envp[j + 1])
				{
					shell->envp[j] = shell->envp[j + 1];
					j++;
				}
				shell->envp[j] = NULL;
				break;
			}
			j++;
		}
		i++;
	}
}
