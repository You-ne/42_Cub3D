/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 07:51:11 by yotillar          #+#    #+#             */
/*   Updated: 2021/01/08 00:47:52 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)

{
	char	red;
	char	green;
	char	blue;

	red = (char)(color & 255);
	green = (char)((color >> 8) & 255);
	blue = (char)((color >> 16) & 255);

/*	printf("Line Size = %d\n", img->s_line);
	printf("Tryng to put a pixel in x = %d, y = %d, with color %d, Index = %d\n", x, y, color, (x*4)+(y*(img->s_line)*4));*/

/*	red = 215;
	blue = 15;
	green = 100;*/

	char	*dst;                                                               /*pad compris l'utilite */

	dst = (char *)img->img + ((y * img->s_line) + (x * 4));
	
	*(dst) = red;
	*(dst + 1) = green;
	*(dst + 2) = blue;


//	if (img->img != NULL)
//	{
//		img->img[((x * 4) + (y * img->s_line))] = (int)red;
//		img->img[((x * 4 + 1) + (y * img->s_line))] = (int)green;
//		img->img[((x * 4 + 2) + (y * img->s_line))] = (int)blue;
//	}
}

void	ft_texture_put(t_img *img, char *texture, int x, int y)
{
	img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = *texture;
	img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = *(texture + 1);
	img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = *(texture + 2);
	img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = *(texture + 3);
}

void	ft_drawcol(t_coor heightncol, t_img tex, t_game game, t_img *img)
{
	int y;
	int count;
	int i;

	y = 0;
	count = 0;
	//printf("\n\n!!!!!!\n\n", (int)(round(heightncol.dist)));
	if (heightncol.y > game.res[1])
	{
		count = (heightncol.y - game.res[1]) / 2;
		heightncol.y = game.res[1];
	}
	while(y < (game.res[1] / 2 + (heightncol.y / 2)))
	{
		if(y > (game.res[1] / 2 - (heightncol.y / 2)))
		{
			//printf("%i;\n\n", (int)(round(((tex.height * count) / heightncol.y))));
			i = (int)round(((double)tex.height / heightncol.y) * (double)count);
			i = i * tex.s_line;
			i = i + ((int)(round(heightncol.dist)) * (tex.bpp / 8));
			//printf(" %i + %i |", ((int)(round(heightncol.dist))), (int)(round(((tex.height * count) / heightncol.y))));
			ft_texture_put(img, &tex.img[i], heightncol.x, y);
			count++;
		}
		else
			ft_pixel_put(img, heightncol.x, y, game.Ce);
		y++;
	}
	while(y < game.res[1])
	{
		ft_pixel_put(img, heightncol.x, y++, game.Fl);
		//y++;
	}
}
