/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:31:01 by antoine           #+#    #+#             */
/*   Updated: 2021/02/25 09:08:57 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"


t_coor	*ft_door_yray(t_coor *ray, t_coor *eq, t_coor *pos, t_coor *dir)
{
	t_coor *door;
	float eqsol;

	door = (struct s_coor*)malloc(sizeof(struct s_coor));

	eqsol = (((int)ray->y + (pos->y < ray->y ? 0.5 : -0.5)) - eq->y) / eq->x;
	eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
	if ((eqsol < (int)ray->x + 1 && eqsol > (int)ray->x))
	{
		door->x = (dir->x != -2) ? eqsol : -1.0;
		door->y = (int)ray->y + (pos->y < ray->y ? 0.5 : -0.5);
	}
	else
	{
		free(door);
		return (NULL);
	}
	return (door);
}

t_coor	*ft_door_xray(t_coor *ray, t_coor *eq, t_coor *pos, t_coor *dir)
{
	t_coor *door;
	float eqsol;

	if (ray->dist == -4)
	{
		door = (struct s_coor*)malloc(sizeof(struct s_coor));

		eqsol = ((int)ray->x + (pos->x < ray->x ? 0.5 : -0.5)) * eq->x + eq->y;
		eqsol = floor(eqsol * pow(10, 5) + 0.5) / pow(10, 5);
		if ((eqsol > (int)ray->y  && eqsol < (int)ray->y + 1))
		{
			door->x = (int)ray->x + (pos->x < ray->x ? 0.5 : -0.5);
			door->y = eqsol;
		}
		else
		{
			free(door);
			return (NULL);
		}
	}
	else if (ray->dist == -5)
		return (ft_door_yray(ray, eq, pos, dir));
	return (door);
}

t_coor	*ft_vertical_door(t_game *game, t_coor *dir, t_coor *ray, int width)
{
	t_coor *door;
	int distproj;

	door = (struct s_coor*)malloc(sizeof(struct s_coor));

	door->x = game->player.pos.x;
	door->x = (float)(((int)(width * door->x)) % width);
	door->dist = fabs(ray->y - game->player.pos.y) + 0.5;
	distproj = ((float)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	door->y = roundf(distproj / door->dist);
	door->dist = (float)((int)ft_ray_collision(game->map, ray, dir));
	door->next = ray->next;
	return (door);
}

void	ft_add_door2(t_game *game, t_coor *door, int width, t_coor *ray)
{
	int distproj;

	if (door->x == (float)((int)door->x + 0.5))
		door->x = (float)(((int)(width * door->y)) % width);
	else if (door->y == (float)((int)door->y + 0.5))
		door->x = (float)(((int)(width * door->x)) % width);
	distproj = ((float)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	door->y = roundf(distproj / door->dist);
}

t_coor	*ft_add_door(t_game *game, t_coor *ray, t_coor *dir, t_coor *eqline)
{
	t_coor *door;
	t_coor vect;
	float eqsol;
	t_img *tex;

	tex = find_sprite(game, ft_ray_collision(game->map, ray, dir));
	if (ray->dist == -3)
		return (ft_vertical_door(game, dir, ray, tex->width));
	else
		door = ft_door_xray(ray, eqline, &game->player.pos, dir);
	if (door == NULL)
		return (NULL);
	vect.x = game->player.pos.x - ray->x; ///////////////fonction calculer angle ?
	vect.y = game->player.pos.y - ray->y;
	vect.dist = (vect.x * game->player.vect.x) + (vect.y * game->player.vect.y);
	vect.dist = vect.dist / (ft_pythagore(vect.x, vect.y) *
	ft_pythagore(game->player.vect.x, game->player.vect.y));
	door->dist = fabs(vect.dist) * ft_pythagore(door->y - game->player.pos.y, 
	door->x - game->player.pos.x);
	ft_add_door2(game, door, tex->width, eqline);
	door->dist = (float)((int)ft_ray_collision(game->map, ray, dir));
	door->next = ray->next;
	return (door);
}
