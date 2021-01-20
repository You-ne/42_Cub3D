/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 23:41:48 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/08 18:45:00 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *pos;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	pos = *alst;
	while (pos->next)
		pos = pos->next;
	pos->next = new;
	new->next = NULL;
	return ;
}
