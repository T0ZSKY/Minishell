/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:41 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/04 14:59:32 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char *expand_variable(char *str, int *index, char **envp)
{
	int     i;
	int     len;
	char    *var_name;
	char    *value;

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
	value = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, var_name, len) == 0 && (*envp)[len] == '=')
		{
			value = ft_strchr(*envp, '=') + 1;
			break;
		}
		envp++;
	}
	free(var_name);
	*index = i + len;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char *handle_quoted_content(char *str, int *i, int *j, char quote, char *result, char **envp)
{
	char *expanded;

	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '"' && str[*i] == '$')
		{
			expanded = expand_variable(str, i, envp);
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

static char *handle_variable(char *str, int *i, int *j, char *result, char **envp)
{
	char *expanded;

	expanded = expand_variable(str, i, envp);
	if (expanded)
	{
		ft_strcpy(&result[*j], expanded);
		*j += ft_strlen(expanded);
		free(expanded);
	}
	return (result);
}

char *process_quotes(char *str, char **envp)
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
			result = handle_quoted_content(str, &i, &j, str[i], result, envp);
		else if (str[i] == '$')
			result = handle_variable(str, &i, &j, result, envp);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void ft_echo(char **tab, char **envp)
{
	int     j;
	int     flag;
	char    *clean;

	j = 1;
	flag = handle_n_flag(tab, &j);
	while (tab[j] && !ft_strchr(tab[j], '|')) // AHAH SOUCIS REGLE
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
}