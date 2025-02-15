/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:48:48 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/15 20:28:55 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

static int	check_first_commands(char **tab, t_shell *shell)
{
	if (ft_strcmp(tab[0], "echo") == 0)
	{
		ft_echo(tab, shell->envp);
		return (0);
	}
	if (ft_strcmp(tab[0], "cd") == 0)
	{
		ft_cd(tab, shell);
		return (0);
	}
	if (ft_strcmp(tab[0], "pwd") == 0)
	{
		ft_pwd(tab);
		return (0);
	}
	if (ft_strcmp(tab[0], "export") == 0)
	{
		ft_export(tab, shell);
		return (0);
	}
	return (-1);
}

static int	check_second_commands(char **tab, t_shell *shell)
{
	if (ft_strcmp(tab[0], "env") == 0)
	{
		ft_env(tab, shell);
		return (0);
	}
	if (ft_strcmp(tab[0], "exit") == 0)
	{
		ft_exit(shell);
		return (0);
	}
	if (ft_strcmp(tab[0], "unset") == 0)
	{
		ft_unset(tab, shell);
		return (0);
	}
	return (1);
}

int	ft_custom_cmd_args(char *cmd, t_shell *shell)
{
	char	**tab;
	int		result;

	tab = ft_split(cmd, ' ');
	if (is_complex(cmd))
		null_complex(tab);
	free(cmd);
	result = check_first_commands(tab, shell);
	if (result == -1)
		return (check_second_commands(tab, shell));
	ft_free_tab(tab);
	return (result);
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
	else
	{
		printf("%s: command not found\n", shell->tab[0]);
		g_last_exit_status = 127;
	}
}

void	ft_lexer(char *input, t_shell *shell)
{
	char	*new_input;

	if (!input)
		return ;
	new_input = strdup(input);
	if (!new_input)
		return ;
	shell->tab = ft_split(new_input, ' ');
	if (!shell->tab || !shell->tab[0])
	{
		free(new_input);
		return ;
	}
	if (is_complex(input))
		ft_handle_pipes(new_input, shell);
	else
		ft_execute_command(shell, new_input);
}
