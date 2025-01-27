/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 18:10:29 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	**skip_pipes(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
		{
			if (!args[i + 1])
				exit(1); //Mais il faudrait ouvrir "pipe>"
			while (args[i + 1])
			{
				free(args[i]);
				args[i] = ft_strdup(args[i + 1]);
				i++;
			}
		}
		i++;
	}
	return (args);
}

void	ft_lexer(char *input, t_shell *shell, char **envp) // fonction qui peux géré les entré
{
	char	*new_input;
	char	**split;

	if (!input)
		return ;
	new_input = replace_pipes(input); //need free
	shell->tab = ft_split(new_input, ' ');
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab);
	else if (is_complex(input))
	{
		free(new_input);
		new_input = ft_strdup(input);
		split = ft_split(new_input, '|');
		split = skip_pipes(split);
		exec_pipes(split, envp);
		//goto pipes
	}
	else
	{
		ft_cmd(shell->tab, envp);
	}
}
