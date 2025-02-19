/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:52:47 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 23:24:16 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_count_word(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		count++;
		if (is_quote(input[i]))
			i = skip_quotes(input, i, input[i]);
		while (input[i] && !is_whitespace(input[i]) && !is_quote(input[i]))
			i++;
	}
	return (count);
}

void	handle_quoted_text(char *str, char *new_str, int *i, int *j)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		new_str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	if (has_unclosed_quotes(str))
	{
		printf("Error: Unclosed quotes detected\n");
		return (NULL);
	}
	new_str = malloc(len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			handle_quoted_text(str, new_str, &i, &j);
		else
		{
			new_str[j++] = str[i++];
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
