/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/30 15:53:03 by taomalbe         ###   ########.fr       */
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

int		is_custom_cmd(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "env") || !ft_strcmp(s, "exit")
		|| !ft_strcmp(s, "unset"))
		return (1);
	return (0);
}

void	ft_custom_cmd(t_shell *shell)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab, shell->envp);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->tab);
	else if (ft_strcmp(shell->tab[0], "pwd") == 0)
		ft_pwd(shell->tab);
	else if (ft_strcmp(shell->tab[0], "export") == 0)
		ft_export(shell->tab, shell);
	else if (ft_strcmp(shell->tab[0], "env") == 0)
		ft_env(shell->tab, shell);
	else if (ft_strcmp(shell->tab[0], "exit") == 0)
		ft_exit(shell);
	else if (ft_strcmp(shell->tab[0], "unset") == 0)
		ft_unset(shell->tab, shell);	
}

void	ft_lexer(char *input, t_shell *shell, char **envp)
{
	char	*new_input;
	char	**split;

	if (!input)
		return ;
	new_input = replace_pipes(input); //need free
	shell->tab = ft_split(new_input, ' ');
	if (!shell->tab[0])
		return ;
	if (is_complex(input))
	{
		free(new_input);
		new_input = ft_strdup(input);
		split = ft_split(new_input, '|');
		split = skip_pipes(split);
		free(new_input);
		exec_pipes(split, envp, shell);
	}
	else
	{
		if (is_custom_cmd(new_input))
			ft_custom_cmd(shell);
		else
			ft_cmd(shell->tab, envp);
	}
}
