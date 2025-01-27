/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:59:13 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/05 10:54:54 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	caract;

	i = 0;
	caract = (char) c;
	while (s[i])
	{
		if (s[i] == caract)
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	if (s[i] == caract)
		return ((char *) &s[i]);
	return (NULL);
}
