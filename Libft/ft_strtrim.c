/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:04:23 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/17 22:59:26 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	int		istart;
	int		iend;

	istart = 0;
	if (!s1 || !set)
		return (NULL);
	iend = ft_strlen((char *)s1) - 1;
	while ((ft_strchr((char *)set, s1[istart]) != 0) && s1[istart])
		istart++;
	if (iend < istart)
		return (ft_strdup(""));
	while (ft_strchr((char *)set, s1[iend]) != 0)
		iend--;
	return (ft_substr(s1, istart, iend - istart + 1));
}
