/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 01:30:13 by yotillar          #+#    #+#             */
/*   Updated: 2019/10/07 01:37:47 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *mem1;
	unsigned char *mem2;

	mem1 = (unsigned char*)s1;
	mem2 = (unsigned char*)s2;
	while (n > 0 && *mem1 == *mem2)
	{
		mem1++;
		mem2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*mem1 - *mem2);
}
