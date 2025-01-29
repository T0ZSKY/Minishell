/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:02:27 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 00:58:41 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

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
