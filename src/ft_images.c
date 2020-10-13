/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 07:51:11 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 20:54:34 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_pixel_put(t_win win, t_img *img, int x, int y, int color)
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

	if (img->img != NULL)
	{
		img->img[((x * 4) + (y * img->s_line))] = red;
		img->img[((x * 4 + 1) + (y * img->s_line))] = green;
		img->img[((x * 4 + 2) + (y * img->s_line))] = blue;
	}
}

void	ft_texture_put(t_win win, t_img *img, char *col, int x, int y)
{
	if (img->img != NULL)
	{
		img->img[((x * img->bpp) + (y * img->s_line))] = col[0];
		img->img[((x * img->bpp + 1) + (y * img->s_line))] = col[1];
		img->img[((x * img->bpp + 2) + (y * img->s_line))] = col[2];
	}
}

void	ft_drawcol(int x, char *col, t_game game, t_img *img)
{
	int y;
	int count;

	y = 0;
	while(y < (game.res[1]/2 + ((ft_strlen(col)/img->bpp)/2)))
	{
		if(y > (game.res[1]/2 - ((ft_strlen(col)/img->bpp)/2)))
		{
			//printf("\nY = %i", y);
			//if textures loaded :
			/*count = 0;
			ft_texture_put(game.win, img, col + (count * img->bpp), x, y);
			count++;*/
			//else :
			ft_pixel_put(game.win, img, x, y, 3348736);
		}
		else
			ft_pixel_put(game.win, img, x, y, game.Ce);
		y++;
	}
	while(y < game.res[1])
	{
		ft_pixel_put(game.win, img, x, y, game.Fl);
		y++;
	}
}
