/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:53:40 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 16:54:41 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char *)s;
	len = ft_strlen(str);
	if ((char)c == '\0')
		return (str + len);
	while (len - 1 >= 0)
	{
		if (str[len - 1] == c)
			return (str + (len - 1));
		len--;
	}
	return (NULL);
}
