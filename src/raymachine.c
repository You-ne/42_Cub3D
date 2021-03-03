/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymachine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:34:58 by antoine           #+#    #+#             */
/*   Updated: 2021/03/03 03:03:53 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_coor		*ft_ray(t_coor *pos, t_coor *dir, t_coor *eqline, t_game *game)
{
	t_coor	*ray;

	if (!(ray = (struct s_coor *)malloc(sizeof(struct s_coor))))
		ft_error("Erreur: Malloc a échoué\n", game);
	ray->x = pos->x;
	ray->y = pos->y;
	ray->dist = -2;
	ray->next = 0x0;
	while (ray->x >= 0 && ray->y >= 0)
	{
		if (dir->x == -2)
		{
			ft_vertical_ray(eqline, dir, ray, game);
			break ;
		}
		ft_xray(eqline, *dir, ray, game);
		if (ray->dist == -1)
			break ;
		ft_yray(eqline, *dir, ray, game);
		if (ray->dist == -1)
			break ;
	}
	return (ray);
}

void		free_ray(t_coor *ray)
{
	t_coor	*p;

	while (ray != NULL)
	{
		p = ray;
		ray = ray->next;
		free(p);
		p = NULL;
	}
}

void		ft_raymachine(t_game *game, t_img *img)
{
	int		x;
	float	angle;
	t_coor	*ray;

	x = 0;
	angle = (float)FOV / (float)game->res[0];
	while (x < game->res[0])
	{
		ray = ft_raycannon(&game->player.pos, &game->player.vect,
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game);
		ft_projection(game, ray, x, img);
		x++;
		free_ray(ray);
	}
	return ;
}

t_coor		*ft_raycannon(t_coor *pos, t_coor *vect, float angle, t_game *game)
{
	float	pente;
	t_coor	*ray;
	t_coor	vecray;
	t_coor	dir;
	t_coor	eqline;

	pente = 0;
	vecray.x = (vect->x * cos(angle)) - (vect->y * sin(angle));
	vecray.y = (vect->x * sin(angle)) + (vect->y * cos(angle));
	if (vecray.x != 0)
		pente = vecray.y / vecray.x;
	eqline.x = pente;
	eqline.y = pos->y - (pente * pos->x);
	dir = ft_dirsteps(vecray);
	ray = ft_ray(pos, &dir, &eqline, game);
	if (dir.x == -2)
		ray->dist = (ray->y - pos->y) < 0 ? -(ray->y - pos->y) : (ray->y -
		pos->y);
	else
		ray->dist = ft_pythagore((ray->x - pos->x), (ray->y - pos->y)) *
		cos(angle);
	return (ray);
}
