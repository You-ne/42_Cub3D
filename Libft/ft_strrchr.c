/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:15:57 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/16 19:00:02 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;

	str = s;
	while (*str)
		str++;
	if (c == 0)
		return ((char*)str);
	else
		while (str >= s)
		{
			if (*str == c)
				return ((char*)str);
			str--;
		}
	return (NULL);
}
