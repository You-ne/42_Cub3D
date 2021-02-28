/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:47:29 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/13 18:50:24 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;

	i = count * size;
	if (!(mem = malloc(i)))
		return (NULL);
	if (size == 0)
		return (mem);
	while (i)
	{
		i--;
		*((unsigned char *)mem + i) = 0;
	}
	return (mem);
}
