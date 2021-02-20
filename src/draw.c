/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:49:59 by antoine           #+#    #+#             */
/*   Updated: 2021/02/20 05:26:45 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"


void	ft_drawcol_sp(t_coor *heightncol, t_game *game, t_img *img, int x)
{
	int count;
	int i;
	t_img tex;
	float size;
	t_coor xy;
	int mid;
	int x1;
	int y1;
	x1 = (int)((heightncol->dist - (int)heightncol->dist) * 1000.0);
	y1 = (int)roundf(((heightncol->dist * 1000) - (int)(heightncol->dist * 1000)) * 1000.0);

	xy.y = 0;
	count = 0;
	size = sp_size((char)((int)heightncol->dist));
	tex = find_sprite(game, (char)((int)heightncol->dist));
	if ((char)((int)heightncol->dist) == '@' || (char)((int)heightncol->dist) == '#'
	|| (char)((int)heightncol->dist) == '!'|| (char)((int)heightncol->dist) == 'H'
	|| (char)((int)heightncol->dist) == 'M')
	{
		tex = enemy_fire_animation(game, &tex, find_enemy(game, x1, y1, (char)((int)heightncol->dist)));
	}
	else if ((char)((int)heightncol->dist) == '+' || (char)((int)heightncol->dist) == '%'
	|| (char)((int)heightncol->dist) == '?' || (char)((int)heightncol->dist) == 'm'
	|| (char)((int)heightncol->dist) == 'h')
	{
		tex = death_animation(game, &tex, find_enemy(game, x1, y1, (char)((int)heightncol->dist)));
	}
	xy.x = x;
	mid = game->tilt + (int)(game->res[1] / 2);
	if (mid + ((heightncol->y * (1 / size)) / 2) -
	heightncol->y < 0)
		count = -1 * (int)(mid + ((heightncol->y *
		(1 / size)) / 2) - heightncol->y);
	while ((float)xy.y <= (mid + ((heightncol->y * (1 / size)) / 2))
	&& xy.y < game->res[1])
	{
		if (xy.y > (mid + ((heightncol->y * (1 / size)) / 2)) - heightncol->y)
		{
			i = (int)(((float)tex.height / heightncol->y) * (float)count);
			i = i * tex.s_line;
			i = i + ((int)(heightncol->x)) * (tex.bpp / 8);
			if ((char)((int)heightncol->dist) == 'P' || (char)((int)heightncol->dist) == 'p')
				ft_texture_put(img, xy.x, xy.y, (tex.img +i));
			else
				ft_texture_put_sp(img, xy, tex.img, i);
			count++;
		}
		xy.y++;
	}
	if (heightncol->next != 0x0)
		ft_drawcol_sp(heightncol->next, game, img, x);
	//free(heightncol);  //// NE FONCTIONNE PAS, GROSSE FUITE DE MEMOIRE !!!
}


void	ft_drawcol(t_coor *heightncol, t_img tex, t_game *game, t_img *img)
{
	int y;
	int count;
	int i;
	int mid;

	y = 0;
	count = 0;
	float distproj;
	if (((int)(heightncol->y - game->res[1]) / 2) - game->tilt > 0)
		count = ((int)(heightncol->y - game->res[1]) / 2) - game->tilt;
	mid = game->tilt + (int)(game->res[1] / 2);
	while ((y < (mid + (heightncol->y / 2)) && y < game->res[1]))
	{
		if (y > mid - (int)(heightncol->y / 2))
		{
			i = (int)(((float)tex.height / heightncol->y) * (float)count);
			i = i * tex.s_line;
			i = i + ((int)(heightncol->x)) * (tex.bpp / 8);
			ft_texture_put(img, heightncol->dist, y, &tex.img[i]);
			count++;
		}
		y++;
	}
	if (heightncol->next != 0x0)
		ft_drawcol_sp(heightncol->next, game, img, heightncol->dist);
}

void draw_sky(t_game *game, t_img *img)
{
	int x;
	int y;
	int i;
	int count;
	float xtex;
	float angle;
	int mid;

	x = 0;
	angle = game->player.vect.y / game->player.vect.x;
	angle = atan(angle);
	angle = (angle * 180) / M_PI;
	mid = game->tilt + (int)(game->res[1] / 2);
	if (game->player.vect.x < 0)
		angle = angle + 180;
	while (x < game->res[0])
	{
		count = (int)(game->res[1]) - game->tilt;
		y = 0;
		xtex = (float)game->SKY.width * ((angle - (FOV / 2)) / 360);
		xtex = xtex + (((float)x / (float)game->res[0]) * ((float)game->SKY.width * ((float)FOV / 360.0)));
		if ((int)xtex < 0)
			xtex = (float)game->SKY.width + xtex;
		if ((int)xtex >= game->SKY.width)
			xtex = xtex - (float)game->SKY.width;
		while (y < game->res[1])
		{
			if (y < mid)
			{
				if (game->SKY.img_p == NULL)
					ft_pixel_put(img, x, y, game->Fl);
				else
				{
					i = (int)(((float)game->SKY.height / ((float)game->res[1] * 1.5)) * (float)count);
					//printf("I=%i; Height=%i; Count=%i\n", i, game->res[1], count);
					i = i * game->SKY.s_line;
					i = i + ((int)(xtex)) * (game->SKY.bpp / 8);
					ft_texture_put(img, x, y, &game->SKY.img[i]);
				}
			}
			else
				ft_pixel_put(img, x, y, game->Fl);
			count = count + 1;
			y++;
		}
		x++;
	}
}



void	draw_weapon(t_game *game, t_img *img, t_img *tex)
{
	int y;
	int x;;
	int i;
	t_coor xy;
	int texy;
	int texx;

	x = (int)((float)game->res[0] / 2) + 3;
	texy = (int)((((float)game->res[1] / 2) - 3));
	texx = (int)((float)game->res[0] / 2) - 3;
	//printf("texwidth=%i; texheight=%i\n\n\n", tex->width, tex->height);
	while (x < game->res[0])
	{
		y = (int)((float)game->res[1] / 2) + 3;
		while (y < game->res[1])
		{
			i = (int)((float)tex->height / (((float)game->res[1] / 2) - 3) * 
			(y - (int)((float)game->res[1] / 2) - 3));
			i = i * tex->s_line;
			i = i + ((int)(((float)tex->width / (((float)game->res[0] / 2) - 3)) * 
			(x - (int)((float)game->res[0] / 2) - 3)) * (tex->bpp / 8));
			xy.x = (float)x;
			xy.y = (float)y;
			//printf("Ytex=%i, Xtex=%i,\n", (int)((float)tex->height / (((float)game->res[1] / 2) - 3) * 
			//(y - (int)((float)game->res[1] / 2) - 3)));
			ft_texture_put_sp(img, xy, tex->img, i);
			y++;
		}
		x++;
	}
}

void	draw_life(t_game *game, t_img *img)
{
	int x;
	int y;
	float mid;

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
			if ((y > (int)(mid - 3) && y < (int)(mid + 3) && 
			((x > (int)((float)(game->res[0] / 2) - (0.10 * (float)game->res[1])) && 
			x < (int)((float)(game->res[0] / 2) - (0.05 * (float)game->res[1]))) || 
			(x < (int)((float)(game->res[0] / 2) + (0.10 * (float)game->res[1])) && 
			x > (int)((float)(game->res[0] / 2) + (0.05 * (float)game->res[1]))))) ||
			((x > (int)((float)(game->res[0] / 2) - 3) && x < (int)((float)(game->res[0] / 2) + 3)) && 
			((y > (int)(mid - (0.10 * (float)game->res[1])) && 
			y < (int)(mid - (0.05 * (float)game->res[1])) || 
			(y < (int)(mid + (0.10 * (float)game->res[1])) && 
			y > (int)(mid + (0.05 * (float)game->res[1])))))))
				ft_pixel_put(img, x, y, 16777215);
			y++;
		}
		x++;
	}
}



