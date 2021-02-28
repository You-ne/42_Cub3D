/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 18:15:32 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/16 18:58:57 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (!dst)
		return (0);
	while (i < dstsize)
	{
		if (src[i] && (i + 1 < dstsize))
		{
			dst[i] = src[i];
			i++;
		}
		if (!src[i] || (i + 1 == dstsize))
		{
			dst[i++] = '\0';
			return (ft_strlen((char*)src));
		}
	}
	return (ft_strlen((char*)src));
}
