/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:14:02 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/11 14:28:25 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int	ft_charset(char c)
{
	if (c == ' ' || c == '|')
		return (1);
	return (0);
}

static size_t	ft_countwords(char const *s)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && ft_charset(s[i]))
			i++;
		if (s[i] && !ft_charset(s[i]))
			words++;
		while (s[i] && !ft_charset(s[i]))
			i++;
	}
	return (words);
}

static size_t	ft_wordlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && !ft_charset(s[i]))
		i++;
	return (i);
}

char	**ft_split_fou(char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**split;

	i = 0;
	j = 0;
	split = (char **)malloc((ft_countwords(s) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i] && j < ft_countwords(s))
	{
		while (s[i] && ft_charset(s[i]))
			i++;
		len = ft_wordlen(s + i);
		split[j] = (char *)malloc((len + 1) * sizeof(char));
		if (!split[j])
			return (NULL);
		ft_strncpy(split[j], s + i, len);
		split[j][len] = '\0';
		i += len;
		j++;
	}
	split[j] = NULL;
	return (split);
}
