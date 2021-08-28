/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 04:24:29 by antoine           #+#    #+#             */
/*   Updated: 2021/03/03 05:06:00 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_col_n_draw(t_game *game, t_coor *ray, t_coor *hnc, t_img *img)
{
	if (game->player.pos.y < ray->y)
	{
		hnc->x = (float)(((int)(game->so.width * ray->x)) % game->so.width);
		ft_drawcol(hnc, &game->so, game, img);
	}
	else
	{
		hnc->x = (float)(((int)(game->no.width * ray->x)) % game->no.width);
		ft_drawcol(hnc, &game->no, game, img);
	}
	return ;
}

int		corner_ray_col(t_game *game, t_coor *ray, t_coor *heightncol,
t_img *img)
{
	if (ray->x == (float)((int)ray->x) && ray->y == (float)((int)ray->y))
	{
		if ((game->player.pos.y > ray->y && game->player.pos.x > ray->x &&
		game->map[(int)ray->y - 1][(int)ray->x] == '1') || (game->player.pos.y >
		ray->y && game->player.pos.x < ray->x &&
		game->map[(int)ray->y - 1][(int)ray->x - 1] == '1'))
		{
			heightncol->x = 0.0;
			ft_drawcol(heightncol, &game->no, game, img);
			return (1);
		}
		if ((game->player.pos.y < ray->y && game->player.pos.x > ray->x &&
		game->map[(int)ray->y][(int)ray->x] == '1') || (game->player.pos.y <
		ray->y && game->player.pos.x < ray->x &&
		game->map[(int)ray->y][(int)ray->x - 1] == '1'))
		{
			heightncol->x = 0.0;
			ft_drawcol(heightncol, &game->so, game, img);
			return (1);
		}
	}
	return (0);
}

void	ft_projection(t_game *game, t_coor *ray, int x, t_img *img)
{
	float	distproj;
	t_coor	hnc;

	hnc = *ray;
	distproj = ((float)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	hnc.y = (float)(int)(distproj / ray->dist);
	hnc.dist = (float)x;
	if (corner_ray_col(game, ray, &hnc, img) == 1)
		return ;
	if (ray->x == (float)((int)ray->x))
	{
		if (game->player.pos.x < ray->x)
		{
			hnc.x = (float)(((int)(game->ea.width * ray->y)) % game->ea.width);
			ft_drawcol(&hnc, &game->ea, game, img);
		}
		else
		{
			hnc.x = (float)(((int)(game->we.width * ray->y)) % game->we.width);
			ft_drawcol(&hnc, &game->we, game, img);
		}
	}
	else
		ray_col_n_draw(game, ray, &hnc, img);
	return ;
}
