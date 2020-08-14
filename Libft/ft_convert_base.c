/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:15:37 by yotillar          #+#    #+#             */
/*   Updated: 2020/02/04 21:04:57 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		len_dest(long nbr, int len_to);
int		ft_len(char *str);

int		get_number(char *nbr, char *base_from, int len_from)
{
	int		i;

	i = 0;
	while (base_from[i])
	{
		if (nbr[len_from] == base_from[i])
			return (i);
		i++;
	}
	return (-1);
}

int		check(char *b)
{
	int		i;
	int		j;

	i = 0;
	while (b[i])
	{
		j = i + 1;
		while (b[j])
		{
			if (b[j] == b[i] || b[i] == '-' || b[i] == '+' ||
				b[i] <= ' ' || b[i] > '~' || b[j] == '-' ||
				b[j] == '+' || b[j] <= ' ' || b[j] > '~')
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

long	atoi_base(char *nbr, char *base_from, int len_from)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] == ' ' || (nbr[i] >= 9 && nbr[i] <= 13))
		i++;
	while (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			sign *= -1;
		i++;
	}
	while (get_number(nbr, base_from, i) != -1)
	{
		res = res * len_from + get_number(nbr, base_from, i);
		i++;
	}
	return (res * sign);
}

void	itoa_base(long nbr, char *base_to, char *res, int len_alloc)
{
	int		len;
	int		neg;

	if (nbr < 0)
	{
		neg = 1;
		nbr *= -1;
		res[0] = '-';
	}
	else
		neg = 0;
	len = ft_len(base_to);
	while (len_alloc > neg)
	{
		res[len_alloc - 1] = base_to[nbr % len];
		nbr /= len;
		len_alloc--;
	}
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*res;
	int		len_from;
	int		len_to;
	int		len_alloc;
	long	value;

	len_from = ft_len(base_from);
	len_to = ft_len(base_to);
	if (check(base_from) == 0 || check(base_to) == 0)
		return (NULL);
	value = atoi_base(nbr, base_from, len_from);
	len_alloc = len_dest(value, len_to);
	if (!(res = malloc(sizeof(char) * (len_alloc + 1))))
		return (NULL);
	itoa_base(value, base_to, res, len_alloc);
	res[len_alloc] = '\0';
	return (res);
}
