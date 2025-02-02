/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:17:21 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 14:53:53 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void	ft_env(char **tab, t_shell *shell)
{
	int	i;

	(void)tab;
	i = 0;
	while (shell->envp && shell->envp[i])
	{
		if (strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
}
