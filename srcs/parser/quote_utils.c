/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 23:15:16 by tomlimon          #+#    #+#             */
/*   Updated: 2025/02/19 23:25:02 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

char	*get_cleaned_token(char *input, int start, int end, int preserve)
{
	char	*token;
	char	*tmp;

	token = ft_substr(input, start, end - start);
	if (!preserve)
	{
		tmp = remove_quotes(token);
		free(token);
		return (tmp);
	}
	return (token);
}

void	add_token(char **tokens, char *token, int *count)
{
	tokens[*count] = token;
	(*count)++;
}

char	**ft_split_quotes(char *input, int preserve_quotes)
{
	int		i;
	int		start;
	char	**tokens;
	int		count;

	i = 0;
	count = 0;
	tokens = malloc(sizeof(char *) * (ft_count_word(input) + 1));
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
		add_token(tokens, get_cleaned_token(input, start, i, preserve_quotes),
			&count);
	}
	tokens[count] = NULL;
	return (tokens);
}

int	has_unclosed_quotes(char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes++;
		else if (str[i] == '"')
			double_quotes++;
		i++;
	}
	return (single_quotes % 2 != 0 || double_quotes % 2 != 0);
}
