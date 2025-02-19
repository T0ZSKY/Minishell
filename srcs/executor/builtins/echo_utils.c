/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:47:35 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 22:37:16 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void	print_clean_str(char *str, int has_next)
{
	printf("%s", str);
	if (has_next)
		printf(" ");
}

int	handle_n_flag(char **tab, int *j)
{
	int	found_n_flag;
	int	i;

	found_n_flag = 0;
	while (tab[*j] && tab[*j][0] == '-')
	{
		i = 1;
		while (tab[*j][i] == 'n')
			i++;
		if (tab[*j][i] == '\0')
		{
			found_n_flag = 1;
			(*j)++;
		}
		else
			break ;
	}
	return (found_n_flag);
}
