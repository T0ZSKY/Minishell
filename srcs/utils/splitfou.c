/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitfou.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:07:29 by taomalbe          #+#    #+#             */
/*   Updated: 2025/01/31 18:24:14 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header/minishell.h"

int ft_is_charset(char c)
{
	if (c == ' ' || c == '|')
		return (1);
	return (0);
}

int countwords(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (ft_is_charset(str[i]) && str[i])
			i++;
		if (!ft_is_charset(str[i]) && str[i])
			words++;
		while (!ft_is_charset(str[i]) && str[i])
			i++;
	}
	return (words);
}

int	wordlen(char *str)
{
	int	i;

	i = 0;
	while (!ft_is_charset(str[i]) && str[i])
		i++;
	return (i);
}



char	**ft_splitfou(char *str)
{
	int		i;
	int		j;
	int		len;
	char	**split;

	split = (char **)malloc((countwords(str) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	len = 0;
	while (j < countwords(str))
	{
		while (ft_is_charset(str[i]) && str[i])
			i++;
		len = wordlen(str + i);
		split[j] = (char *)malloc((len + 1) * sizeof(char));
		if (!split[j])
			return (NULL);
		split[j] = ft_strncpy(split[j], str + i, len);
		j++;
	}
	split[j] = NULL;
	return (split);
}
