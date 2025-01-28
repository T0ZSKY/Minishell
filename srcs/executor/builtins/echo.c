/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:41 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 02:31:29 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char	*expand_variable(char *str, int *index)
{
	int		i;
	int		len;
	char	*var_name;
	char	*value;

	i = *index + 1;
	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[i], len);
	var_name[len] = '\0';
	value = getenv(var_name);
	free(var_name);
	*index = i + len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char *handle_quoted_content(char *str, int *i, int *j, char quote, char *result)
{
	char *expanded;

	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i] == '$')
		{
			expanded = expand_variable(str, i);
			if (expanded)
			{
				ft_strcpy(&result[*j], expanded);
				*j += ft_strlen(expanded);
				free(expanded);
			}
		}
		else
			result[(*j)++] = str[(*i)++];
	}
	if (str[*i])
		(*i)++;
	return (result);
}

static char *handle_variable(char *str, int *i, int *j, char *result)
{
	char *expanded;

	expanded = expand_variable(str, i);
	if (expanded)
	{
		ft_strcpy(&result[*j], expanded);
		*j += ft_strlen(expanded);
		free(expanded);
	}
	return (result);
}

char *process_quotes(char *str)
{
	int     i;
	int     j;
	char    *result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			result = handle_quoted_content(str, &i, &j, str[i], result);
		else if (str[i] == '$')
			result = handle_variable(str, &i, &j, result);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static void print_clean_str(char *str, int has_next)
{
	printf("%s", str);
	if (has_next)
		printf(" ");
}

static int handle_n_flag(char **tab, int *j)
{
	if (tab[1] && ft_strcmp(tab[1], "-n") == 0)
	{
		*j = 2;
		return (1);
	}
	return (0);
}

void ft_echo(char **tab)
{
	int     j;
	int     flag;
	char    *clean;

	j = 1;
	flag = handle_n_flag(tab, &j);
	while (tab[j])
	{
		clean = process_quotes(tab[j]);
		if (!clean)
		{
			ft_putstr_fd("Error: Unclosed quotes\n", 2);
			return ;
		}
		print_clean_str(clean, tab[j + 1] != NULL);
		free(clean);
		j++;
	}
	if (flag == 0)
		printf("\n");
}
