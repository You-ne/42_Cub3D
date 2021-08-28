/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:24:36 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 19:57:19 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	res;
	char			*i;

	i = dest;
	while (*i && i < dest + size)
		i++;
	while (*src && (i < dest + size - 1))
		*i++ = *src++;
	res = i - dest;
	if (i < dest + size)
		*i = '\0';
	while (*src++)
		res++;
	return (res);
}
