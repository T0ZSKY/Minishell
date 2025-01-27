/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:24:39 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/07 21:34:04 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	lst = lst->next;
	new_elem = new_list;
	while (lst)
	{
		new_elem->next = ft_lstnew(f(lst->content));
		if (!new_elem->next)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_elem = new_elem->next;
		lst = lst->next;
	}
	return (new_list);
}
