/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:47:45 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/07 23:42:11 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] && str[i] != sep)
			count++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

char	*cpy(char *str, char c)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof (char) * (i + 1));
	while (i > j)
	{
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tab = malloc(sizeof (char *) * (ft_count((char *)s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[j] = cpy((char *) &s[i], c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
