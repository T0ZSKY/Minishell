/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 17:58:57 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_lexer(char *input, t_shell *shell) // fonction qui peux géré les entré
{
	shell->tab = ft_split(input, ' ');

	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab);
}
