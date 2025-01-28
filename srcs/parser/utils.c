/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:54 by taomalbe          #+#    #+#             */
/*   Updated: 2025/01/28 10:12:59 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	is_complex(char *input)
{
	if (ft_strstr(input, "|") || ft_strstr(input, ">")
		|| ft_strstr(input, ">>") || ft_strstr(input, "<")
		|| ft_strstr(input, "<<"))
		return (1);
	return (0);
}
