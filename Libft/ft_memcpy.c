/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:26:16 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/10 22:01:34 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*memdst;
	unsigned char	*memsrc;
	size_t			count;

	count = 0;
	memdst = (unsigned char*)dst;
	memsrc = (unsigned char*)src;
	if (!dst && !src && n != 0)
		return (NULL);
	while (count < n)
	{
		memdst[count] = memsrc[count];
		count++;
	}
	return (dst);
}
