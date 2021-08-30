#include "../cub3d.h"

void		ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->img + ((y * img->s_line) + (x * 4));
	*(int*)dst = color;
}

void		ft_texture_put_sp(t_img *img, t_coor xy, char *texture, int i)
{
	int		x;
	int		y;

	x = (int)xy.x;
	y = (int)xy.y;
	if (texture[i] == 0 && texture[i + 1] == 0 && texture[i + 2] == 0)
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = (char)1;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = (char)1;
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = (char)1;
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = (char)127;
	}
	else if (texture[i] != texture[0] || texture[i + 1] != texture[1] ||
	texture[i + 2] != texture[2])
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = texture[i];
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] =
		texture[i + 1];
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] =
		texture[i + 2];
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] =
		texture[i + 3];
	}
}

void		ft_texture_put(t_img *img, int x, int y, char *texture)
{
	if (*texture == 0 && *(texture + 1) == 0 && *(texture + 2) == 0)
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = 127;
	}
	else
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = *texture;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] =
		*(texture + 1);
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] =
		*(texture + 2);
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] =
		*(texture + 3);
	}
}

void		end_screen(t_game *game, t_img *tex, t_img *img)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = 0;
	while (x < game->res[0])
	{
		y = 0;
		j = ((int)(((float)tex->width / game->res[0]) * (float)x));
		while (y < game->res[1])
		{
			i = (int)(((float)tex->height / game->res[1]) * (float)y);
			i = i * tex->s_line;
			i = i + (j * 4);
			ft_texture_put(img, x, y, &tex->img[i]);
			y++;
		}
		x++;
	}
}
