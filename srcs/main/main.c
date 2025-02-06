/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:58 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/06 16:47:53 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

	int g_last_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
	char	*input;
	int i;

	t_shell	shell;

	i = 0;
	if (argc && argv)
		shell.is_running = 1;
	increment_shell_level();
	ft_ascii();
	shell.envp = init_shell(envp)->envp;
	signal(SIGINT, ctrl_c_handler);  // Ctrl-C
	signal(SIGQUIT, SIG_IGN); //
	while (shell.is_running)
	{
		input = readline("\033[31mminishell » \033[0m"); // entré de l'utilisateur
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			shell.is_running = 0;
			break ;
		}
		else// a faire regarder si il y a un pip ou une redirection pour l'envoyé dans une fonction fait expres genre ft_complex
			ft_lexer(input, &shell);
		if (shell.tab)
			ft_free_tab(shell.tab);
		add_history(input);
		free(input);
	}
	clear_history();
	if (shell.envp)
	{
    	i = 0;
    	while (shell.envp[i])
        	free(shell.envp[i++]);
    	free(shell.envp);
	}

}
