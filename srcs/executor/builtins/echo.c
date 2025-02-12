/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:41 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/12 14:26:13 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char	*expand_variable(char *str, int *index, char **envp)
{
	int		i;
	int		len;
	char	*var_name;
	char	*value;

	i = *index + 1;
	if (str[*index + 1] == '?')
		return (handle_exit_status(index));
	len = get_var_length(str, i);
	var_name = get_var_name(str, i, len);
	if (!var_name)
		return (NULL);
	value = find_env_value(var_name, len, envp);
	free(var_name);
	*index = i + len;
	return (value);
}

static char	*handle_quotes(t_echo_data *data, char *str, char quote)
{
	char	*expanded;

	data->i++;
	while (str[data->i] && str[data->i] != quote)
	{
		if (quote == '"' && str[data->i] == '$')
		{
			expanded = expand_variable(str, &(data->i), data->envp);
			if (expanded)
			{
				ft_strcpy(&data->result[data->j], expanded);
				data->j += ft_strlen(expanded);
				free(expanded);
			}
		}
		else
			data->result[data->j++] = str[data->i++];
	}
	if (str[data->i])
		data->i++;
	return (data->result);
}

static char	*handle_dollar(t_echo_data *data, char *str)
{
	char	*expanded;

	expanded = expand_variable(str, &(data->i), data->envp);
	if (expanded)
	{
		ft_strcpy(&data->result[data->j], expanded);
		data->j += ft_strlen(expanded);
		free(expanded);
	}
	return (data->result);
}

char	*process_quotes(char *str, char **envp)
{
	t_echo_data	data;

	data.envp = envp;
	data.i = 0;
	data.j = 0;
	data.result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!data.result)
		return (NULL);
	while (str[data.i])
	{
		if (str[data.i] == '\'' || str[data.i] == '"')
			data.result = handle_quotes(&data, str, str[data.i]);
		else if (str[data.i] == '$')
			data.result = handle_dollar(&data, str);
		else
			data.result[data.j++] = str[data.i++];
	}
	data.result[data.j] = '\0';
	return (data.result);
}

void ft_echo(char **tab, char **envp, int complex)
{
	int		j;
	int		flag;
	char	*clean;

	j = 1;
	flag = handle_n_flag(tab, &j);
	while (tab[j] && (!ft_strchr(tab[j], '|') || !complex)) // AHAH SOUCIS REGLE 2
	{
		clean = process_quotes(tab[j], envp);
		if (!clean)
		{
			ft_putstr_fd("Error: Unclosed quotes\n", 2);
			return ;
		}
		print_clean_str(clean, tab[j + 1] != NULL && ft_strcmp(tab[j + 1], "|") != 0);
		free(clean);
		j++;
	}
	if (flag == 0)
		printf("\n");
	g_last_exit_status = 0;
}
