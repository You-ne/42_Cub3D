/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/14 08:36:52 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char 	*extractt_path(char *dest, char *str)
{
	int	i;

	i = 0;
	while(str[i] != ' ')
		i++;
	if(!(dest = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i] != ' ')
		dest[i] = str[i++];
	dest[i] = '\0';
	return(dest);
}
