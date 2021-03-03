/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:49:59 by antoine           #+#    #+#             */
/*   Updated: 2021/03/03 05:11:30 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		draw_sky2(t_game *game, t_img *img, int x, float xtex)
{
	int		y;
	int		i;
	int		count;

	y = 0;
	count = (int)(game->res[1]) - game->tilt;
	while (y < game->res[1])
	{
		if (y < game->tilt + (int)(game->res[1] / 2))
		{
			if (game->sky.img_p == NULL)
				ft_pixel_put(img, x, y++, game->ce);
			else
			{
				i = (int)(((float)game->sky.height / ((float)game->res[1] *
				1.5)) * (float)count++);
				i = i * game->sky.s_line;
				i = i + ((int)(xtex)) * (game->sky.bpp / 8);
				ft_texture_put(img, x, y++, &game->sky.img[i]);
			}
		}
		else
			ft_pixel_put(img, x, y++, game->fl);
	}
	return ;
}

void		draw_sky(t_game *game, t_img *img)
{
	int		x;
	float	xtex;
	float	angle;

	x = 0;
	angle = game->player.vect.y / game->player.vect.x;
	angle = atanf(angle);
	angle = (angle * 180) / M_PI;
	if (game->player.vect.x < 0)
		angle = angle + 180;
	while (x < game->res[0])
	{
		xtex = (float)game->sky.width * ((angle - (FOV / 2)) / 360);
		xtex = xtex + (((float)x / (float)game->res[0]) *
		((float)game->sky.width * ((float)FOV / 360.0)));
		if ((int)xtex < 0)
			xtex = (float)game->sky.width + xtex;
		if ((int)xtex >= game->sky.width)
			xtex = xtex - (float)game->sky.width;
		draw_sky2(game, img, x, xtex);
		x++;
	}
	return ;
}

void		draw_weapon(t_game *game, t_img *img, t_img *tex)
{
	int		y;
	int		x;
	int		i;
	t_coor	xy;

	x = (int)((float)game->res[0] / 2) + 3;
	while (x < game->res[0])
	{
		y = (int)((float)game->res[1] / 2) + 3;
		while (y < game->res[1])
		{
			i = (int)((float)tex->height / (((float)game->res[1] / 2) - 3) *
			(y - (int)((float)game->res[1] / 2) - 3));
			i = i * tex->s_line;
			i = i + ((int)(((float)tex->width / (((float)game->res[0] / 2) -
			3)) * (x - (int)((float)game->res[0] / 2) - 3)) * (tex->bpp / 8));
			xy.x = (float)x;
			xy.y = (float)y;
			ft_texture_put_sp(img, xy, tex->img, i);
			y++;
		}
		x++;
	}
	return ;
}

int			draw_hud(t_game *game, int x, int y)
{
	float	mid;

	mid = (float)game->res[1] / 2;
	if ((y > (int)(mid - 3) && y < (int)(mid + 3) &&
	((x > (int)((float)(game->res[0] / 2) - (0.10 * (float)game->res[1])) &&
	x < (int)((float)(game->res[0] / 2) - (0.05 * (float)game->res[1]))) ||
	(x < (int)((float)(game->res[0] / 2) + (0.10 * (float)game->res[1])) &&
	x > (int)((float)(game->res[0] / 2) + (0.05 * (float)game->res[1]))))) ||
	((x > (int)((float)(game->res[0] / 2) - 3) && x <
	(int)((float)(game->res[0] / 2) + 3)) && (((y > (int)(mid - (0.10 *
	(float)game->res[1])) && y < (int)(mid - (0.05 * (float)game->res[1]))) ||
	(y < (int)(mid + (0.10 * (float)game->res[1])) &&
	y > (int)(mid + (0.05 * (float)game->res[1])))))))
		return (1);
	return (0);
}

void		draw_life(t_game *game, t_img *img)
{
	int		x;
	int		y;
	float	mid;

	mid = (float)game->res[1] / 2;
	x = 0;
	while (x < game->res[0])
	{
		y = 0;
		while (y < game->res[1])
		{
			if (y > (int)(mid * (2 - ((float)game->player.pv / 100))) &&
			x < game->res[0] / 50)
				ft_pixel_put(img, x, y, 9175040);
			if (draw_hud(game, x, y) == 1)
				ft_pixel_put(img, x, y, 16777215);
			y++;
		}
		x++;
	}
	return ;
}
