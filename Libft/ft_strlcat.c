/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 03:06:16 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/16 18:35:04 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			res;
	char			*d;

	d = dst;
	while (*d && d < dst + dstsize)
		d++;
	while (*src && (d < dst + dstsize - 1))
		*d++ = *src++;
	res = d - dst;
	if (d < dst + dstsize)
		*d = '\0';
	while (*src++)
		res++;
	return (res);
}
