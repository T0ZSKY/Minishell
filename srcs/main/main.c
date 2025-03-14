/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:58 by tomlimon          #+#    #+#             */
/*   Updated: 2025/03/14 04:44:40 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	g_last_exit_status = 0;

void	free_shell_env(t_shell *shell)
{
	int	i;

	if (shell->envp)
	{
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
	}
}

static void	handle_input(char *input, t_shell *shell)
{
	if (!input)
	{
		printf("exit\n");
		shell->is_running = 0;
		return ;
	}
	if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
		shell->is_running = 0;
		return ;
	}
	if (input[0] != '\0')
		add_history(input);
	ft_lexer(input, shell);
	if (shell->tab)
		ft_free_tab(shell->tab);
	free(input);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (shell->is_running)
	{
		if (g_last_exit_status == 130)
			printf("\r");
		input = readline("\033[31mminishell » \033[0m");
		handle_input(input, shell);
	}
	clear_history();
}

void	init_shell_env(t_shell *shell, char **envp, int argc, char **argv)
{
	t_shell	*tmp;

	if (argc && argv)
		shell->is_running = 1;
	ft_ascii();
	tmp = init_shell(envp);
	shell->envp = tmp->envp;
	free(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	init_shell_env(&shell, envp, argc, argv);
	init_signals();
	shell_loop(&shell);
	free_shell_env(&shell);
	return (0);
}
