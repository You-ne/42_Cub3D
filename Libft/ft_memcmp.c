/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:49:16 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/14 18:49:37 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ptr_1;
	const unsigned char *ptr_2;

	ptr_1 = (const unsigned char*)s1;
	ptr_2 = (const unsigned char*)s2;
	while (n)
	{
		if (*ptr_1 != *ptr_2)
			return ((int)(*ptr_1 - *ptr_2));
		n--;
		ptr_1++;
		ptr_2++;
	}
	return (0);
}
