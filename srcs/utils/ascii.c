/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:42:31 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/11 14:27:14 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

void	ft_ascii(void)
{
	printf("\033[38;5;213m");
	printf("Minishell by\n");
	printf("taomalbe\n");
	printf("and\n");
	printf("tomlimon\n");
	printf("\033[0m");
}
