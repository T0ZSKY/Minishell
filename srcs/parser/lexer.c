/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 15:46:28 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_lexer(char *input, t_shell *shell, char **envp) // fonction qui peux géré les entré
{
	char	*new_input;
	char	**split;

	if (!input)
		return ;
	shell->tab = ft_split(input, ' ');
	new_input = replace_pipes(input);
	printf("%s\n", new_input);
	split = ft_split(new_input, ' ');
	printf("%s\n", split[0]);
	printf("%s\n", split[1]);
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab);
	else if (is_complex(input))
	{
		new_input = replace_pipes(input);
		split = ft_split(new_input, ' ');
		printf("%s", new_input);
		exec_pipes(split, envp);
		//goto pipes
	}
	else
	{
		ft_cmd(shell->tab, envp);
	}
}
