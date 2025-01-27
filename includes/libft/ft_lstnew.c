/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:04 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/06 14:54:53 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nod;

	nod = malloc(sizeof (t_list));
	if (!nod)
		return (NULL);
	nod->content = content;
	nod->next = NULL;
	return (nod);
}
