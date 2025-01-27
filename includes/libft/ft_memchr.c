/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:13:56 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/05 11:35:30 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (void *) s;
	while (i < n)
	{
		if (str[i] == (char) c)
		{
			return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	const char str[] = "Hello, world!";
	int c = 'o';
	size_t n = strlen(str);

	void *result_std = memchr(str, c, n);
	void *result_ft = ft_memchr(str, c, n);
	
	printf("Test 1: Recherche du caractère 'o' dans \"%s\"\n", str);
	printf("memchr : %s\n", result_std ? (char *)result_std : "NULL");
	printf("ft_memchr : %s\n", result_ft ? (char *)result_ft : "NULL");

	return 0;
}
*/