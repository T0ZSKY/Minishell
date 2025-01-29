/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:47:45 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/28 22:02:13 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**split;

	i = 0;
	j = 0;
	split = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i] && j < ft_countwords(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		len = ft_wordlen(s + i, c);
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
