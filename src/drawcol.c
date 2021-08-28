/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawcol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 06:40:06 by antoine           #+#    #+#             */
/*   Updated: 2021/03/03 04:06:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_drawcol_sp2(t_coor *heightncol, t_game *gam, t_img *img, t_coor *xy)
{
	int		mid;
	int		i;
	float	size;
	t_img	*tex;

	tex = img->next;
	size = sp_size((char)((int)heightncol->dist));
	mid = gam->tilt + (int)(gam->res[1] / 2);
	if (xy->y > (mid + ((heightncol->y * (1 / size)) / 2)) - heightncol->y)
	{
		i = (int)(((float)tex->height / heightncol->y) * xy->dist);
		i = i * tex->s_line;
		i = i + ((int)(heightncol->x)) * (tex->bpp / 8);
		if ((char)((int)heightncol->dist) != 'P' &&
		(char)((int)heightncol->dist) != '*')
			ft_texture_put_sp(img, *xy, tex->img, i);
		else
			ft_texture_put(img, xy->x, xy->y, (tex->img + i));
		xy->dist = xy->dist + 1;
	}
	return ;
}

void	ft_drawcol_sp(t_coor *heightncol, t_game *game, t_img *img, int x)
{
	t_img	*tex;
	float	size;
	t_coor	xy;
	int		mid;

	xy.y = 0;
	size = sp_size((char)((int)heightncol->dist));
	tex = find_sprite(game, (char)((int)heightncol->dist));
	tex = find_animation(game, heightncol->coor_sp, tex,
	(char)((int)heightncol->dist));
	img->next = tex;
	xy.x = x;
	mid = game->tilt + (int)(game->res[1] / 2);
	xy.dist = (mid + ((heightncol->y * (1 / size)) / 2) - heightncol->y < 0) ?
	(float)(-1 * (int)(mid + ((heightncol->y * (1 / size)) / 2) -
	heightncol->y)) : 0;
	while ((float)xy.y < (mid + ((heightncol->y * (1 / size)) / 2))
	&& xy.y < game->res[1])
	{
		ft_drawcol_sp2(heightncol, game, img, &xy);
		xy.y++;
	}
	if (heightncol->next != 0x0)
		ft_drawcol_sp(heightncol->next, game, img, x);
}

t_coor	*suppr_sp_behind_door(t_coor *hnc)
{
	t_coor	*tmp;
	t_coor	*tmp2;
	int		i;

	tmp = hnc;
	i = 0;
	while (!(tmp->next == 0x0 || (char)((int)tmp->next->dist) == 'P' ||
	(char)((int)tmp->next->dist) == '*'))
	{
		tmp = tmp->next;
		i++;
	}
	if (i == 0 || tmp->next == 0x0 || ((char)((int)tmp->next->dist) != 'P' &&
	(char)((int)tmp->next->dist) != '*'))
		return (hnc);
	hnc = hnc->next;
	i--;
	while (hnc != tmp && i > 0)
	{
		tmp2 = hnc->next;
		hnc = tmp2;
		i--;
	}
	return (hnc);
}

void	ft_drawcol(t_coor *heightncol, t_img *tex, t_game *game, t_img *img)
{
	int	y;
	int	count;
	int	i;

	y = 0;
	count = 0;
	if (((int)(heightncol->y - game->res[1]) / 2) - game->tilt > 0)
		count = ((int)(heightncol->y - game->res[1]) / 2) - game->tilt;
	while ((y < ((game->tilt + (int)(game->res[1] / 2)) + (heightncol->y / 2))
	&& y < game->res[1]))
	{
		if (y > game->tilt + (int)(game->res[1] / 2) - (int)(heightncol->y / 2))
		{
			i = (int)(((float)tex->height / heightncol->y) * (float)count);
			i = i * tex->s_line;
			i = i + ((int)(heightncol->x)) * (tex->bpp / 8);
			ft_texture_put(img, heightncol->dist, y, &tex->img[i]);
			count++;
		}
		y++;
	}
	i = (int)heightncol->dist;
	heightncol = suppr_sp_behind_door(heightncol);
	if (heightncol->next != 0x0)
		ft_drawcol_sp(heightncol->next, game, img, i);
}
