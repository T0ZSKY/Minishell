/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:49:51 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 23:50:12 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void ft_cd(char **tab)
{
	if (!tab[1])
	{
		chdir(getenv("HOME"));
		return;
	}
	if (chdir(tab[1]) == -1)
		printf("cd: %s: No such file or directory\n", tab[1]);
}
