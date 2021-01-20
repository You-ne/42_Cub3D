/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:25:14 by yotillar          #+#    #+#             */
/*   Updated: 2020/02/04 21:05:27 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			len_dest(long nbr, int len_to)
{
	int		len;
	long	nb;

	nb = nbr;
	len = 0;
	if (nb < 0)
		nb *= -1;
	while (nb >= len_to)
	{
		len++;
		nb /= len_to;
	}
	len++;
	if (nbr < 0)
		len++;
	return (len);
}

int			ft_len(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
