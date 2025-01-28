/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:47:35 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 23:48:07 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void print_clean_str(char *str, int has_next)
{
	printf("%s", str);
	if (has_next)
		printf(" ");
}

int handle_n_flag(char **tab, int *j)
{
	if (tab[1] && ft_strcmp(tab[1], "-n") == 0)
	{
		*j = 2;
		return (1);
	}
	return (0);
}
