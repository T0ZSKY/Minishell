/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:54 by taomalbe          #+#    #+#             */
/*   Updated: 2025/01/28 15:49:06 by taomalbe         ###   ########.fr       */
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

char	*replace_pipes(char *cmd)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = (char *)malloc((ft_strlen(cmd) + 1) * sizeof(char));
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		if (new_cmd[i] == '|')
			new_cmd[i] = ' ';
		i++;
	}
	new_cmd[i] = '\0';
	return (new_cmd);
}
