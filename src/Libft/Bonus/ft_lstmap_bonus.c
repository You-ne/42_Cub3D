/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:51:07 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/08 19:03:41 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*previous;
	t_list	*pos;

	if (lst && f)
	{
		if (!(start = ft_lstnew_bonus(f(lst))))
			return (NULL);
		lst = lst->next;
		previous = start;
		while (lst)
		{
			if (!(pos = ft_lstnew_bonus(f(lst))))
				return (NULL);
			previous->next = pos;
			previous = pos;
			lst = lst->next;
		}
		return (start);
	}
	return (NULL);
}
