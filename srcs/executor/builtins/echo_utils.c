/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:47:35 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/31 20:29:25 by tomlimon         ###   ########.fr       */
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
