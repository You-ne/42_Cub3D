/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 23:14:24 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/08 18:45:19 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*pos;

	if (lst)
	{
		pos = lst;
		count = 0;
		while (pos)
		{
			pos = pos->next;
			count++;
		}
		return (count);
	}
	return (0);
}
