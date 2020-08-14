/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 23:30:00 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/08 18:42:58 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_lsit	*pos;

	if (lst)
	{
		pos = lst;
		while (pos->next)
			pos = pos->next;
		return (pos);
	}
	return (NULL);
}
