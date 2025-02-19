/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:52:47 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 10:40:55 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	skip_quotes(char *str, int i, char quote)
{
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
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

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new_str[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	**ft_split_quotes(char *input, int preserve_quotes)
{
	int		i;
	int		start;
	char	**tokens;
	char	*tmp;
	int		count;

	i = 0;
	count = 0;
	tokens = malloc(sizeof(char *) * (ft_count_word(input) + 1));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		start = i;
		if (is_quote(input[i]))
			i = skip_quotes(input, i, input[i]);
		while (input[i] && !is_whitespace(input[i]))
			i++;
		tokens[count] = ft_substr(input, start, i - start);
		if (!preserve_quotes)
		{
			tmp = remove_quotes(tokens[count]);
			free(tokens[count]);
			tokens[count] = tmp;
		}
		count++;
	}
	tokens[count] = NULL;
	return (tokens);
}
