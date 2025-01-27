/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:40:07 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/07 16:27:14 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *)s;
	while (b[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (&b[i]);
		else
			i--;
	}
	return (NULL);
}
