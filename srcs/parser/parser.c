/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:18:54 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/15 20:33:52 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_handle_pipes(char *input, t_shell *shell)
{
	char	**split;

	split = ft_split(input, '|');
	free(input);
	exec_pipes(split, shell);
	ft_free_tab(split);
}

void	ft_execute_command(t_shell *shell, char *input)
{
	if (is_custom_cmd(shell->tab[0]) == 1)
		ft_custom_cmd(shell);
	else
		ft_cmd(shell->tab, shell->envp, shell);
	if (!is_complex(input))
		free(input);
}
