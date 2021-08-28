/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:10:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 04:09:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char		ft_ray_collision(char **map, t_coor *ray, t_coor *dir)
{
	int		i;
	int		j;

	i = (dir->x <= 0) ? -1 : 0;
	j = (dir->y <= 0) ? -1 : 0;
	if (ray->x == ((float)((int)ray->x)) && ray->y == ((float)((int)ray->y)))
	{
		if (map[(int)ray->y + j][(int)ray->x + i] != '0')
			return (map[(int)ray->y + j][(int)ray->x + i]);
	}
	else if (ray->x == (float)((int)ray->x))
	{
		if (map[(int)ray->y][(int)ray->x + i] != '0')
			return (map[(int)ray->y][(int)ray->x + i]);
	}
	else
	{
		if (map[(int)ray->y + j][(int)ray->x] != '0')
			return (map[(int)ray->y + j][(int)ray->x]);
	}
	return ('0');
}

void		ft_verif_ray_collision(t_game *game, t_coor *ray, t_coor *dir,
t_coor *eqline)
{
	t_coor	*sp;

	if (ft_ray_collision(game->map, ray, dir) == '1')
	{
		ray->dist = -1;
		return ;
	}
	else if (ft_ray_collision(game->map, ray, dir) == 'P' ||
	ft_ray_collision(game->map, ray, dir) == 'p' ||
	ft_ray_collision(game->map, ray, dir) == '*')
	{
		sp = ft_add_door(game, ray, dir, eqline);
		ray->next = (sp != NULL) ? sp : ray->next;
	}
	else if (ft_ray_collision(game->map, ray, dir) != '0')
	{
		sp = ft_add_sprite(game, ray, dir, eqline);
		sp->dist = (float)((int)ft_ray_collision(game->map, ray, dir));
		ray->next = (sp->x != -1) ? sp : ray->next;
		sp->x == -1 ? free(sp) : 0;
	}
}

void		ft_xray(t_coor *eqline, t_coor dir, t_coor *ray, t_game *game)
{
	float	eqsol;
	int		midcase;

	eqsol = ((int)ray->x + dir.x) * eqline->x + eqline->y;
	eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
	ray->dist = -4;
	midcase = (dir.y == 0 && ray->y == (float)((int)ray->y) &&
	ray->x != (float)((int)ray->x)) ? -1 : 0;
	while ((eqsol >= (int)ray->y + midcase && eqsol <= (int)ray->y + midcase +
	1) || (eqsol == (float)((int)eqsol) && (eqsol >= (int)ray->y + midcase &&
	eqsol <= (int)ray->y + midcase + 1)))
	{
		ray->x = (int)ray->x + dir.x;
		ray->y = eqsol;
		ft_verif_ray_collision(game, ray, &dir, eqline);
		if (ray->dist == -1)
			return ;
		dir.x = ((dir.x == 0.0) ? -1.0 : dir.x);
		eqsol = ((int)ray->x + dir.x) * eqline->x + eqline->y;
		eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
		midcase = (dir.y == 0 && ray->y == (float)((int)ray->y)) ? -1 : 0;
	}
	ray->dist = 1;
}

void		ft_yray(t_coor *eqline, t_coor dir, t_coor *ray, t_game *game)
{
	float	eqsol;
	int		midcase;

	eqsol = (((int)ray->y + dir.y) - eqline->y) / eqline->x;
	eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
	ray->dist = -5;
	midcase = (dir.x == 0 && (ray->x == (float)((int)ray->x))) ? -1 : 0;
	while ((eqsol <= (int)ray->x + midcase + 1 && eqsol >= (int)ray->x +
	midcase) || (eqsol == (float)((int)eqsol) && (eqsol >= (int)ray->x + midcase
	&& eqsol <= (int)ray->x + midcase + 1)))
	{
		ray->x = (dir.x != -2) ? eqsol : ray->x;
		ray->y = (int)ray->y + dir.y;
		ft_verif_ray_collision(game, ray, &dir, eqline);
		if (ray->dist == -1)
			return ;
		dir.y = (dir.y == 0) ? -1 : dir.y;
		eqsol = (((int)ray->y + dir.y) - eqline->y) / eqline->x;
		eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
		midcase = (dir.x == 0 && ray->x == (float)((int)ray->x)) ? -1 : 0;
	}
	ray->dist = 1;
}

void		ft_vertical_ray(t_coor *eqline, t_coor *dir, t_coor *ray,
t_game *game)
{
	ray->dist = -3;
	if (dir->y > 0)
		ray->y = (float)((int)ray->y + 1);
	else
		ray->y = (ray->y == (float)((int)ray->y)) ? (float)((int)ray->y - 1) :
		(float)((int)ray->y);
	while (ft_ray_collision(game->map, ray, dir) != '1')
	{
		ft_verif_ray_collision(game, ray, dir, eqline);
		if (dir->y > 0)
			ray->y = (float)((int)ray->y + 1);
		else
			ray->y = (ray->y == (float)((int)ray->y)) ?
			(float)((int)ray->y - 1) : (float)((int)ray->y);
	}
}
