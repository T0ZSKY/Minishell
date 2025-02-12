/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:18:46 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/12 14:29:40 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char	*handle_exit_status(int *index)
{
	char	*status_str;

	status_str = ft_itoa(g_last_exit_status);
	*index += 2;
	return (status_str);
}

int	get_var_length(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	return (len);
}

char	*get_var_name(char *str, int i, int len)
{
	char	*var_name;

	if (len == 0)
		return (ft_strdup("$"));
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[i], len);
	var_name[len] = '\0';
	return (var_name);
}

char	*find_env_value(char *var_name, int len, char **envp)
{
	char	*value;

	value = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, var_name, len) == 0 && (*envp)[len] == '=')
		{
			value = ft_strchr(*envp, '=') + 1;
			break ;
		}
		envp++;
	}
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
