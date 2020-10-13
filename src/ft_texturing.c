/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:39:13 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 19:56:47 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

char	*ft_extract_col_texture(t_img texture, int ncol)
{
	int i;
	int j;
	char *dest;
	char *add;

	i = ncol * texture.bpp;
	dest = ft_strdup("");
	while (i > ft_strlen(texture.img))
	{
		add = ft_strdup("");
		j = 0;
		while (j < texture.bpp)
			add = ft_strmcat(add, ft_ctostr(1, texture.img[i + j++]));
		dest = ft_strmcat(dest, add);
		free(add);
		i = i + *texture.width;
	}
	return (dest);
}

char	*ft_resize_col_texture(t_img texture, int height, int ncol)
{
	int i;
	int j;
	int count;
	char *dest;
	char *tex_col;
	char *add;

	i = 0;
	j = 0;
	count = 1;
	tex_col = ft_extract_col_texture(texture, ncol);
	dest = ft_strdup("");
	while (i < CUB_SIZE / texture.bpp)
	{
		if (i != (CUB_SIZE - 1) / texture.bpp && ft_strncmp(ft_substr(tex_col, i, texture.bpp), ft_substr(tex_col, i + texture.bpp, texture.bpp), INT_MAX) == 0)  //texture[i] == texture[i + 1])
			count++;
		else
		{
			j = 0;
			while (j < (int)(round((height * count) / CUB_SIZE)))
			{
				dest = ft_strmcat(dest, add = ft_substr(tex_col, i ,texture.bpp));
				free(add);
			}
			count = 1;
		}
		i = i + texture.bpp;
	}
	if (ft_strlen(dest) > height)
		printf("Trop grand");
	else if (ft_strlen(dest) < height)
		printf("Trop petit");
	return (dest);
}
