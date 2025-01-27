/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:56:06 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/06 00:52:04 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(int n)
{
	int	count;

	count = 1;
	if (n < 0)
		count++;
	while (n / 10 != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void	fill_number(char *number, int n, int len)
{
	if (n < 0)
	{
		number[0] = '-';
		while (n != 0)
		{
			number[len--] = '0' - (n % 10);
			n /= 10;
		}
	}
	else
	{
		while (n != 0)
		{
			number[len--] = '0' + (n % 10);
			n /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*number;

	len = count_digits(n);
	number = (char *)malloc(len + 1);
	if (!number)
		return (NULL);
	number[len--] = '\0';
	if (n == 0)
		number[0] = '0';
	else
		fill_number(number, n, len);
	return (number);
}
