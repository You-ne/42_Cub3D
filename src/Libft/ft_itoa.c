/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 19:06:07 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/10 18:22:25 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		len_alloc(long n)
{
	int		len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len += 1;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	int		neg;
	char	*res;

	nb = n;
	neg = 0;
	if (nb < 0)
	{
		neg = 1;
		nb *= -1;
	}
	len = (len_alloc(nb) + neg);
	if (!(res = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (neg == 1)
		res[0] = '-';
	res[len] = '\0';
	while (len > neg)
	{
		res[len - 1] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (res);
}
