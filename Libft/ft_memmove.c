/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:32:48 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/13 18:50:54 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*strsrc;
	char	*strdst;

	strsrc = (char*)src;
	strdst = (char*)dst;
	if (!dst && !src && len != 0)
		return (NULL);
	if (strsrc < strdst)
	{
		strsrc = strsrc + len - 1;
		strdst = strdst + len - 1;
		while (len > 0)
		{
			*strdst-- = *strsrc--;
			len--;
		}
	}
	else
		while (len > 0)
		{
			*strdst++ = *strsrc++;
			len--;
		}
	return (dst);
}
