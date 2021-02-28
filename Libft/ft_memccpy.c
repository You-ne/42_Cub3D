/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:46:17 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/10 22:05:17 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*memdst;
	unsigned char	*memsrc;
	size_t			i;

	i = 0;
	memdst = (unsigned char*)dst;
	memsrc = (unsigned char*)src;
	while (i < n && memsrc[i] != (unsigned char)c)
	{
		memdst[i] = memsrc[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		memdst[i] = memsrc[i];
		i++;
		return (&memdst[i]);
	}
}
