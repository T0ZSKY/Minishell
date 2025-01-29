/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:58 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/29 15:16:08 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	if (argc && argv)
		shell.is_running = 1;
	increment_shell_level();
	ft_ascii();
	shell.envp = init_shell(envp)->envp;
	signal(SIGINT, ctrl_c_handler);  // Ctrl-C
	signal(SIGQUIT, ctrl_back_handler); // Ctrl-\ -
	signal(SIGTSTP, ctrl_d_handler); // Ctrl-D
	while (shell.is_running)
	{
		input = readline("\033[31mminishell » \033[0m"); // entré de l'utilisateur
		if (!input)
		{
			free(input);
			printf("exit\n");
			break ;
		}
		else// a faire regarder si il y a un pip ou une redirection pour l'envoyé dans une fonction fait expres genre ft_complex
			ft_lexer(input, &shell, envp);
		add_history(input);
		free(input);
	}
	clear_history();
	if (shell.envp)
	{
		while (*shell.envp)
			free(*shell.envp++);
		free(shell.envp);
	}
}
