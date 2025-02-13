/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:00:49 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/11 17:01:51 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	charset_complex(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*uncomplex_input(char *input)
{
	int		i;
	int		flag;
	char	*c_input;

	i = 0;
	flag = 0;
	c_input = ft_strdup(input);
	while (c_input[i])
	{
		if (c_input[i] == '"' && flag == 1)
			break ;
		if (c_input[i] == '"' && flag == 0)
			flag = 1;
		if (flag == 1 && charset_complex(c_input[i]))
			c_input[i] = ' ';
		i++;
	}
	return (c_input);
}

int	is_complex(char *input)
{
	int		i;
	int		flag;
	char	*c_input;

	i = 0;
	flag = 0;
	c_input = ft_strdup(input);
	while (c_input[i])
	{
		if (c_input[i] == '"' && flag == 1)
			break ;
		if (c_input[i] == '"' && flag == 0)
			flag = 1;
		if (flag == 1 && charset_complex(c_input[i]))
			c_input[i] = ' ';
		i++;
	}
	if (ft_strstr(c_input, "|") || ft_strstr(c_input, ">")
		|| ft_strstr(c_input, ">>") || ft_strstr(c_input, "<")
		|| ft_strstr(c_input, "<<"))
		return (free(c_input), 1);
	return (free(c_input), 0);
}