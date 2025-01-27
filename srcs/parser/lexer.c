/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 23:50:49 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ft_lexer(char *input, t_shell *shell, char **envp) // fonction qui peux géré les entré
{
	shell->tab = ft_split(input, ' ');

	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->tab);
	//sinon appelé fonction qui gere fonction non builtin
	else
	{
		ft_cmd(shell->tab, envp);
	}
}
