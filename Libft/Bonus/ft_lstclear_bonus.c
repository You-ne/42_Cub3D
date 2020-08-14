/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 00:07:22 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/07 00:10:14 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *pos;

	if (lst)
	{
		while (*lst)
		{
			pos = *lst->next;
			ft_lstdelone(*lst, del);
			*lst = pos;
		}
	}
}
