/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:01:38 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 19:57:45 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	if (!dest || !src)
		return (0);
	while (src[i] != '\0')
		i++;
	len = i;
	if (size == 0)
	{
		return (len);
	}
	else
	{
		i = 0;
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		return (len);
	}
}
