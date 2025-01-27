/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 17:54:34 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_lexer(char *input, t_shell *shell) // fonction qui peux géré les entré
{
	shell->tab = ft_split(input, ' ');

	if (shell->tab)
	{
		int i = 0;
		while (shell->tab[i])
		{
			printf("tab[%d] = %s\n", i, shell->tab[i]);
			i++;
		}
	}
	else
		printf("error\n");
}
