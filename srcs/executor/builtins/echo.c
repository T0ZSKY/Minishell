/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:59:41 by tomlimon          #+#    #+#             */
/*   Updated: 2025/01/27 18:08:58 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/header/minishell.h"

char *ft_quote(char *str)
{
	int i;
	int j;
	char *new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i++;
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void ft_echo(char **tab)
{
	int i;

	i = 1;
	while (tab[i])
	{
		if (ft_strchr(tab[i], 34) || ft_strchr(tab[i], 39))
			tab[i] = ft_quote(tab[i]);
		printf("%s", tab[i]);
		i++;
		if (tab[i])
			printf(" ");
	}
	printf("\n");
}
