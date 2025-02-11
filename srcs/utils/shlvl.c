/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:02:27 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/11 14:19:13 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	increment_shell_level(void)
{
	char	*shlvl;
	int		new_shlvl;
	char	*new_shlvl_str;

	shlvl = getenv("SHLVL");
	new_shlvl = 1;
	if (shlvl != NULL)
		new_shlvl = ft_atoi(shlvl) + 1;
	new_shlvl_str = ft_itoa(new_shlvl);
	if (new_shlvl_str)
	{
		setenv("SHLVL", new_shlvl_str, 1);
		free(new_shlvl_str);
	}
}
