/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:46:26 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/14 18:46:42 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_calloc(size_t nmemb, size_t size)
{
	void		*res;
	size_t		i;

	i = size * nmemb;
	if (!(res = malloc(i)))
		return (NULL);
	if (i == 0)
		return (res);
	while (i)
	{
		--i;
		*((unsigned char*)res + i) = 0;
	}
	return (res);
}
