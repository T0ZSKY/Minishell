/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/07 09:30:18 by taomalbe         ###   ########.fr       */
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
	if (ft_strstr(s, "echo") || ft_strstr(s, "cd") || ft_strstr(s, "pwd")
		|| ft_strstr(s, "export") || ft_strstr(s, "env") || ft_strstr(s, "exit")
		|| ft_strstr(s, "unset"))
		return (1);
	return (0);
}

int	ft_custom_cmd_args(char *cmd, t_shell *shell)
{
	char **tab;

	tab = ft_split(cmd, 32);
	if (ft_strcmp(tab[0], "echo") == 0)
	{
		ft_echo(tab, shell->envp);
		return (0);
	}
	else if (ft_strcmp(tab[0], "cd") == 0)
	{
		ft_cd(tab, shell);
		return (0);	
	}
	else if (ft_strcmp(tab[0], "pwd") == 0)
	{
		ft_pwd(tab);
		return (0);
	}
	else if (ft_strcmp(tab[0], "export") == 0)
	{
		ft_export(tab, shell);
		return (0);
	}
	else if (ft_strcmp(tab[0], "env") == 0)
	{
		ft_env(tab, shell);
		return (0);
	}
	else if (ft_strcmp(tab[0], "exit") == 0)
	{
		ft_exit(shell);
		return (0);
	}
	else if (ft_strcmp(tab[0], "unset") == 0)
	{
		ft_unset(tab, shell);
		return (0);
	}
	else
		return (1);
}

void	ft_custom_cmd(t_shell *shell)
{
	if (ft_strcmp(shell->tab[0], "echo") == 0)
		ft_echo(shell->tab, shell->envp);
	else if (ft_strcmp(shell->tab[0], "cd") == 0)
		ft_cd(shell->tab, shell);
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

//Attention split envoie un tableau de tableau rempli et donc export bug car !tab[1]

void	ft_lexer(char *input, t_shell *shell)
{
	char	*new_input;
	char	**split;

	if (!input)
		return ;
	new_input = strdup(input); //need free
	shell->tab = ft_split(new_input, ' ');
	if (!shell->tab[0])
		return ;
	if (is_complex(input))
	{
		split = ft_split(new_input, '|');
		free(new_input);
		exec_pipes(split, shell->envp, shell);
	}
	else
	{
		if (is_custom_cmd(shell->tab[0]) == 1)
			ft_custom_cmd(shell);
		else
			ft_cmd(shell->tab, shell->envp, shell);
	}
}
