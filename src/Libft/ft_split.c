/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 17:38:08 by yotillar          #+#    #+#             */
/*   Updated: 2020/01/13 21:40:32 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			c_w(char *str, char c)
{
	int		words;

	words = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			words++;
			while (*str && *str != c)
				str++;
		}
	}
	return (words);
}

int			len_word(char *str, char c)
{
	int		len;

	len = 0;
	while (*str == c && *str)
		str++;
	while (*str != c && *str)
	{
		str++;
		len++;
	}
	return (len);
}

char		*ft_dup(char *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	if (!(dest = (char *)malloc(sizeof(*dest) * (len_word(src, c) + 1))))
		return (NULL);
	i = 0;
	while (*src && *src != c)
	{
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(*tab) * (c_w((char*)s, c) + 1))))
		return (NULL);
	i = 0;
	str = (char*)s;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			tab[i] = ft_dup(str, c);
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	tab[i] = 0;
	return (tab);
}
