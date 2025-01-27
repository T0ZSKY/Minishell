/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:37:58 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/07 18:14:38 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*result;

	i = -1;
	if (s1 && s2)
	{
		size1 = ft_strlen(s1);
		size2 = ft_strlen(s2);
		result = malloc(sizeof (char) * (size1 + size2 + 1));
		if (!result)
			return (NULL);
		while (s1[++i])
			result[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			result[size1] = s2[i];
			size1++;
		}
		result[size1] = '\0';
		return (result);
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s", ft_strjoin("je", "test"));
}
*/