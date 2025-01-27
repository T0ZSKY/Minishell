/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:14:44 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/05 10:55:14 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

int main()
{
    char buffer[20];

    memset(buffer, 'A', sizeof(buffer) - 1);
    buffer[19] = '\0';

    printf("Avant bzero : %s\n", buffer);

    bzero(buffer, 10);

    printf("Après bzero : ");
    for (int i = 0; i < 20; i++)
    {
        if (buffer[i] == '\0')
            printf("\\0");
        else
            printf("%c", buffer[i]);
    }
    printf("\n");

    return 0;
}
*/