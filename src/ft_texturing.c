/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:39:13 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/12 11:56:54 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

char	*ft_resize_col_texture(char **texture, int height, int ncol)
{
	int i;
	int j;
	int count;
	char *dest;
	char *add;

	i = 0;
	j = 0;
	count = 1;
	dest = ft_strdup("");
	while (i < CUB_SIZE)
	{
		if (i != CUB_SIZE - 1 && texture[i][ncol] == texture[i + 1][ncol])
			count++;
		else
		{
			dest = ft_strmcat(dest, add = ft_ctostr((int)(round((height * count) 
			/ CUB_SIZE)), texture[i][ncol])); ////arrondi bancaire ??
			free(add);
			count = 1;
		}
		i++;
	}
	if (ft_strlen(dest) > height)
		printf("Trop grand");
	else if (ft_strlen(dest) < height)
		printf("Trop petit");
	return (dest);
}
