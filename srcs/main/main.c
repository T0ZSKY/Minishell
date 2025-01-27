/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:58 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 17:40:14 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int main(int argc, char **argv, char **env)
{
	int i;
	t_shell shell;
	char *input;

	shell.is_running = 1;
	while (shell.is_running)
	{
		input = readline("\033[31mminishell » \033[0m");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			shell.is_running = 0;
			break;
		}
		printf("%s\n", input);
	}
}
