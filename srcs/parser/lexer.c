/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:42:36 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_lexer(char *input, t_shell *shell) // fonction qui peux géré les entré
{
	if (!input)
		return ;
	shell->tab = ft_split(input, ' ');
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab);
}
