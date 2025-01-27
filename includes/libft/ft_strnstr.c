/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:38:27 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/06 13:44:09 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *) big);
	i = 0;
	j = 0;
	while (big[i])
	{
		j = 0;
		while (big[i] == little[j] && big[i] && i < len)
		{
			i++;
			j++;
		}
		if (!little[j])
			return ((char *) &big[i - j]);
		i = (i - j) + 1;
	}
	return (NULL);
}

/*
#include <stdio.h>

int main() {
    const char *big = "Hello, this is a test string.";
    const char *little = "test";
    size_t len = 11;  // Length to search in 'big'

    char *result = strnstr(big, little, len);
    
    if (result) {
        printf("Found substring: \"%s\"\n", result);
    } else {
        printf("Substring not found.\n");
    }

    return 0;
}
*/