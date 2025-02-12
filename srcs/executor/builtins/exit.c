/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:08:32 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/11 15:31:56 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

void	ft_exit(t_shell *shell)
{
	if (shell->tab[1])
		exit(ft_atoi(shell->tab[1]));
	else
		exit(0);
	shell->is_running = 0;
}
