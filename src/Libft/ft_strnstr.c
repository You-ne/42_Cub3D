/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 03:12:08 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/16 18:59:50 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	unsigned int	i;
	char			*start;

	start = (char *)big;
	i = 0;
	if (small[0] == '\0')
		return ((char *)big);
	while (*big && small[i] && (big < start + len))
	{
		i = 0;
		while (big[i] == small[i] && (big[i] && small[i]) &&
			((big + i) < (start + len)))
		{
			if (small[i + 1] == '\0')
				return ((char *)big);
			i++;
		}
		big++;
	}
	return (NULL);
}
