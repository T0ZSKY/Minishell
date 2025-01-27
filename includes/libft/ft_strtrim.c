/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:51:52 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/05 21:36:52 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpy(int start, int end, char const *s1)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i] = s1[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_end(char const *s1, char const *set, int start)
{
	int	end;
	int	i;

	i = start;
	end = start;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i + 1;
		i++;
	}
	return (ft_cpy(start, end, s1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	start = i;
	return (ft_end(s1, set, start));
}
/*
#include <stdio.h>

int main() {
    char *s1 = "xaxaxaxahello worldxaxaxaxaxa";
    char *set = "xa";
    char *result = ft_strtrim(s1, set);
    printf("Result: %s\n", result);
    free(result);  
    return 0;
}
*/