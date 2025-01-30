/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:13:02 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/30 16:21:08 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void ctrl_c_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}
