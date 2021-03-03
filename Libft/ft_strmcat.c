/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:28:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 04:45:21 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmcat(char *src, char *add)
{
	char	*dest;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(src) + ft_strlen(add);
	i = 0;
	j = 0;
	if (!(dest = malloc(sizeof(char) * size + 1)) || !src || !add)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (add[j] != '\0')
	{
		dest[i] = add[j];
		i++;
		j++;
	}
	dest[size] = '\0';
	free(src);
	return (dest);
}
