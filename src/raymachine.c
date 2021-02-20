/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymachine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:34:58 by antoine           #+#    #+#             */
/*   Updated: 2021/02/18 09:40:09 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_coor	ft_ray(t_coor pos, t_coor dir, t_coor eqline, t_game *game)
{
	t_coor ray;

	ray.x = pos.x;
	ray.y = pos.y;
	ray.dist = -2;
	ray.next = 0x0;
//	printf("Ray fired!\n", ray.x, ray.y);
	while (ray.x >= 0 && ray.y >= 0)
	{
		//printf("Calculating ray...\n");
		if (dir.x == -2)
		{
			ray = ft_vertical_ray(eqline, dir, ray, game);
			break;
		}
		ray = ft_Xray(eqline, dir, ray, game);
		if (ray.dist == -1)
			break;
		ray = ft_Yray(eqline, dir, ray, game);
		if (ray.dist == -1)
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
		ray = ft_raycannon(game->player.pos, game->player.vect, 
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game);
		ft_projection(game, ray, x, img);
		x++;
	}
	return ;
}

t_coor	ft_raycannon(t_coor pos, t_coor vect, float angle, t_game *game)
{
	float pente;
	float x0;
	t_coor ray;
	t_coor vecray;
	t_coor dir;
	t_coor eqline;

	//printf("Cannon firing!\n");
	pente = 0;
	vecray.x = (vect.x * cos(angle)) - (vect.y * sin(angle));
	vecray.y = (vect.x * sin(angle)) + (vect.y * cos(angle));
	if (vecray.x != 0)
		pente = vecray.y / vecray.x;
	x0 =  pos.y - (pente * pos.x);
	eqline.x = pente;
	eqline.y = x0;
	dir = ft_dirsteps(vecray);
	ray = ft_ray(pos, dir, eqline, game);
	if (dir.x == -2)
		ray.dist = (ray.y - pos.y) < 0 ? -(ray.y - pos.y) : (ray.y - pos.y);
	else
		ray.dist = ft_pythagore((ray.x - pos.x), (ray.y - pos.y)) * cos(angle);
//	printf("Cannon Rearming!\n");
	return (ray);
}


void	ft_projection(t_game *game, t_coor ray, int x, t_img *img)
{
	int		height;
	int		ncol;
	void	*test;
	float	distproj;
	t_coor	heightncol;

	distproj = ((float)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	heightncol.y = (float)(int)(distproj / ray.dist);
	//ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE; // Texture change avec distance
	heightncol.dist = (float)x;
	heightncol.next = ray.next;
	if (ray.x == (float)((int)ray.x))
	{
		if (game->player.pos.x < ray.x)
		{
			heightncol.x = (float)(((int)(game->WE.width * ray.y)) % game->WE.width);
			ft_drawcol(&heightncol, game->WE, game, img);
		}
		else
		{
			heightncol.x = (float)(((int)(game->EA.width * ray.y)) % game->EA.width);
			ft_drawcol(&heightncol, game->EA, game, img);
		}
	}
	else
	{
		if (game->player.pos.y < ray.y)
		{
			heightncol.x = (float)(((int)(game->NO.width * ray.x)) % game->NO.width);
			ft_drawcol(&heightncol, game->NO, game, img);
		}
		else
		{
			heightncol.x = (float)(((int)(game->SO.width * ray.x)) % game->SO.width);
			ft_drawcol(&heightncol, game->SO, game, img);
		}
	}
	//printf("  ncol = %f\n", heightncol.dist);
	return ;
}

