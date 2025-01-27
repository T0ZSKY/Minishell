/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:42:06 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/07 16:09:17 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*de;
	char	*sr;

	sr = (char *) src;
	de = (char *) dest;
	i = 0;
	if (de > sr)
	{
		while (n > 0)
		{
			n--;
			de[n] = sr[n];
		}
	}
	else if (de < sr)
	{
		while (i < n)
		{
			de[i] = sr[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>

int main()
{
    char buffer[20] = "Hello, world!";

    printf("Avant memmove : %s\n", buffer);

    memmove(buffer + 7, buffer, 5);

    printf("Après memmove : %s\n", buffer);

    return 0;
}
*/
