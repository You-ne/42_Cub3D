/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 07:51:11 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/09 01:06:28 by antoine          ###   ########.fr       */
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
	*(int*)dst = color;
//	*(dst) = red;
//	*(dst + 1) = green;
//	*(dst + 2) = blue;


//	if (img->img != NULL)
//	{
//		img->img[((x * 4) + (y * img->s_line))] = (int)red;
//		img->img[((x * 4 + 1) + (y * img->s_line))] = (int)green;
//		img->img[((x * 4 + 2) + (y * img->s_line))] = (int)blue;
//	}
}

t_img find_sprite(t_game *game, char chr)
{
	t_img *tex;

	tex = &game->SP;
	while (tex->chr != chr)
		tex = tex->next;
	return (*tex);
}

void	ft_texture_put_sp(t_img *img, t_coor xy, char *texture, int i)
{
	int x;
	int y;

	x = (int)xy.x;
	y = (int)xy.y;
	//printf("%d ; ", (int)*(texture + 3));
	if (LINUX != 1 || (LINUX == 1 && (texture[i] != texture[0] && 
	texture[i + 1] != texture[1] && texture[i + 2] != texture[0])))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = texture[i];
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = texture[i + 1];
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = texture[i + 2];
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = texture[i + 3];
	}
}

void	ft_texture_put(t_img *img, int x, int y, char *texture)
{
	//printf("%d ; ", (int)*(texture + 3));
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = *texture;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = *(texture + 1);
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = *(texture + 2);
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = *(texture + 3);
}

void	ft_drawcol_sp(t_coor *heightncol, t_game *game, t_img *img, int x)
{
	int count;
	int i;
	t_img tex;
	double size;
	t_coor xy;
	int mid;

	xy.y = 0;
	count = 0;
	size = sp_size((char)((int)heightncol->dist));
	tex = find_sprite(game, (char)((int)heightncol->dist));
	xy.x = x;
	if (game->accroupi == 0)
		mid = game->res[1] / 2;
	else
		mid = game->res[1] / 4;
	if (mid + ((heightncol->y * (1 / size)) / 2) -
	heightncol->y < 0)
		count = -1 * (int)(mid + ((heightncol->y *
		(1 / size)) / 2) - heightncol->y);
	while((double)xy.y <= (mid + ((heightncol->y * (1 / size)) / 2))
	&& xy.y < game->res[1])
	{
		if (xy.y > (mid + ((heightncol->y * (1 / size)) / 2)) - heightncol->y)
		{
			i = (int)(((double)tex.height / heightncol->y) * (double)count);
			i = i * tex.s_line;
			i = i + ((int)(heightncol->x)) * (tex.bpp / 8);
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
	double distproj;
	if (heightncol->y > game->res[1])
		count = (int)(heightncol->y - game->res[1]) / 2;
	if (game->accroupi == 0)
		mid = game->res[1] / 2;
	else
		mid = game->res[1] / 4;
	while ((y < (mid + (heightncol->y / 2)) && y < game->res[1]))
	{
		if (y > (mid - (heightncol->y / 2)))
		{
			i = (int)(((double)tex.height / heightncol->y) * (double)count);
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
	float xtex;
	float angle;
	int mid;

	x = 0;
	angle = game->player.vect.y / game->player.vect.x;
	angle = atan(angle);
	angle = (angle * 180) / M_PI;
	if (game->accroupi == 0)
		mid = game->res[1] / 2;
	else
		mid = game->res[1] / 4;

	if (game->player.vect.x < 0)
		angle = angle + 180;
	while (x < game->res[0])
	{
		y = 0;
		xtex = (double)game->SKY.width * ((angle - (FOV / 2)) / 360);
		xtex = xtex + (((double)x / (double)game->res[0]) * ((double)game->SKY.width * ((double)FOV / 360.0)));
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
					i = (int)(((double)game->SKY.height / (double)game->res[1]) * (double)y);
					i = i * game->SKY.s_line;
					i = i + ((int)(xtex)) * (game->SKY.bpp / 8);
					ft_texture_put(img, x, y, &game->SKY.img[i]);
				}
			}
			else
				ft_pixel_put(img, x, y, game->Fl);
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

	mid = (double)game->res[1] / 2;
	x = 0;
	while (x < game->res[0])
	{
		y = 0;
		while (y < game->res[1])
		{
			if (y > (int)(mid * (2 - ((double)game->player.pv / 100))) && 
			x < game->res[0] / 50)
				ft_pixel_put(img, x, y, 9175040);
			if ((y > (int)(mid - 3) && y < (int)(mid + 3) && 
			((x > (int)((double)(game->res[0] / 2) - (0.10 * (double)game->res[1])) && 
			x < (int)((double)(game->res[0] / 2) - (0.05 * (double)game->res[1]))) || 
			(x < (int)((double)(game->res[0] / 2) + (0.10 * (double)game->res[1])) && 
			x > (int)((double)(game->res[0] / 2) + (0.05 * (double)game->res[1]))))) ||
			((x > (int)((double)(game->res[0] / 2) - 3) && x < (int)((double)(game->res[0] / 2) + 3)) && 
			((y > (int)(mid - (0.10 * (double)game->res[1])) && 
			y < (int)(mid - (0.05 * (double)game->res[1])) || 
			(y < (int)(mid + (0.10 * (double)game->res[1])) && 
			y > (int)(mid + (0.05 * (double)game->res[1])))))))
				ft_pixel_put(img, x, y, 16777215);
			y++;
		}
		x++;
	}
}

t_img	*weapon_fire_animation(t_game *game, t_img *weapon)
{
	clock_t	t2;
	float	centisec;

	if (game->fire == 1)
	{
		t2 = clock();
		centisec = ((double)(t2 - game->fire_t1) / CLOCKS_PER_SEC) * 100;
//		printf("Centisec=%f; t1=%ld; t2=%ld; CPS=%ld\n\n", centisec, (long)game->fire_t1, (long)t2, CLOCKS_PER_SEC);
		if ((int)centisec % 33 < 11)
		{
			weapon_fire(game);
			return (weapon->next);
		}
		if ((int)centisec % 33 >= 11 && (int)centisec % 33 < 22)
			return (weapon->next->next);
	}
	return (weapon);
}

void	draw_weapon(t_game *game, t_img *img, t_img *tex)
{
	int y;
	int x;;
	int i;
	t_coor xy;
	int texy;
	int texx;

	x = (int)((double)game->res[0] / 2) + 3;
	texy = (int)((((double)game->res[1] / 2) - 3));
	texx = (int)((double)game->res[0] / 2) - 3;
	//printf("texwidth=%i; texheight=%i\n\n\n", tex->width, tex->height);
	while (x < game->res[0])
	{
		y = (int)((double)game->res[1] / 2) + 3;
		while (y < game->res[1])
		{
			i = (int)((double)tex->height / (((double)game->res[1] / 2) - 3) * 
			(y - (int)((double)game->res[1] / 2) - 3));
			i = i * tex->s_line;
			i = i + ((int)(((double)tex->width / (((double)game->res[0] / 2) - 3)) * 
			(x - (int)((double)game->res[0] / 2) - 3)) * (tex->bpp / 8));
			xy.x = (double)x;
			xy.y = (double)y;
			//printf("Ytex=%i, Xtex=%i,\n", (int)((double)tex->height / (((double)game->res[1] / 2) - 3) * 
			//(y - (int)((double)game->res[1] / 2) - 3)));
			ft_texture_put_sp(img, xy, tex->img, i);
			y++;
		}
		x++;
	}
}
