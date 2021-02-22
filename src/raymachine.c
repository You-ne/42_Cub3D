/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymachine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:34:58 by antoine           #+#    #+#             */
/*   Updated: 2021/02/22 07:33:28 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_coor	ft_ray(t_coor *pos, t_coor *dir, t_coor *eqline, t_game *game)
{
	t_coor *ray;

	ray->x = pos->x;
	ray->y = pos->y;
	ray->dist = -2;
	ray->next = 0x0;
	while (ray->x >= 0 && ray->y >= 0)
	{
		if (dir->x == -2)
		{
			ray = ft_vertical_ray(eqline, dir, ray, game);
			break;
		}
		ray = ft_Xray(eqline, dir, ray, game);
		if (ray->dist == -1)
			break;
		ray = ft_Yray(eqline, dir, ray, game);
		if (ray->dist == -1)
			break;
	}
	return (ray);
}

void	ft_raymachine(t_game *game, t_img *img)
{
	int	x;
	float	angle;
	float	distproj;
	t_coor	ray;
	t_img	weapon;

	x = 0;
	angle = (float)FOV / (float)game->res[0];
	while (x < game->res[0])
	{
		ray = ft_raycannon(game->player->pos, game->player->vect, 
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game);
		ft_projection(game, ray, x, img);
		x++;
	}
	return ;
}

t_coor	ft_raycannon(t_coor *pos, t_coor *vect, float angle, t_game *game)
{
	float pente;
	float x0;
	t_coor *ray;
	t_coor *vecray;
	t_coor *dir;
	t_coor *eqline;

	pente = 0;
	vecray->x = (vect->x * cos(angle)) - (vect->y * sin(angle));
	vecray->y = (vect->x * sin(angle)) + (vect->y * cos(angle));
	if (vecray->x != 0)
		pente = vecray->y / vecray->x;
	x0 =  pos->y - (pente * pos->x);
	eqline->x = pente;
	eqline->y = x0;
	dir = ft_dirsteps(vecray);
	ray = ft_ray(pos, dir, eqline, game);
	if (dir->x == -2)
		ray->dist = (ray->y - pos->y) < 0 ? -(ray->y - pos->y) :
		(ray->y - pos->y);
	else
		ray->dist = ft_pythagore((ray->x - pos->x), (ray->y - pos->y)) *
		cos(angle);
	return (ray);
}
