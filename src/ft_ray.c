/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:10:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/01/07 23:56:21 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

double	ft_pythagore(double x, double y)
{
	double sqr;
	double dist;

	sqr = (x * x)  + (y * y);
	dist = sqrt(sqr);
	return (dist);
}

int	ft_ray_collision(char **map, t_coor ray, t_coor dir)
{
	int i;

	i = 0;
	if (ray.x == ((double)((int)ray.x)) && ray.y == ((double)((int)ray.y)))
	{
		if (dir.x <= 0)
			i = -1;
		if (dir.y <= 0)
			i = -1;
		if (map[(int)ray.y + i][(int)ray.x + i] == '1')
			return (1);
	}
	else if (ray.x == (double)((int)ray.x))
	{
		if (dir.x <= 0)
			i = -1;
		//printf("RayX = %f, RayY = %f\n\n", ray.x, ray.y);
		if (map[(int)ray.y][(int)ray.x + i] == '1')
			return (1);
	}
	else
	{
		if (dir.y <= 0)
			i = -1;
		if (map[(int)ray.y + i][(int)ray.x] == '1')
			return (1);
	}
	return(0);
}

t_coor	ft_Xray(t_coor eqline, t_coor dir, t_coor ray, char **map)
{
	double eqsol;
	int midcase;

	//printf("X");
	midcase = 0;
	eqsol = ((int)ray.x + dir.x) * eqline.x + eqline.y;
	eqsol = floor(eqsol * pow(10, 14) + 0.5) / pow(10, 14);
	if (dir.y == 0 && ray.y == (double)((int)ray.y) && ray.x != (double)((int)ray.x))///)
		midcase = -1;
	while ((eqsol > (int)ray.y + midcase && eqsol < (int)ray.y + midcase + 1) || 
	(eqsol == (int)eqsol))
	{
		ray.x = (int)ray.x + dir.x;
		ray.y = eqsol;
		if (ft_ray_collision(map, ray, dir) == 1)
		{
			ray.dist = 0;
			return (ray);
		}
		if (dir.x == 0)
			dir.x = -1;
		eqsol = ((int)ray.x + dir.x) * eqline.x + eqline.y;
		if (dir.y == 0 && ray.y == (double)((int)ray.y) ) //&& ray.x != (double)((int)ray.x)))
			midcase = -1;
		else
			midcase = 0;
	}
	ray.dist = 1;
	return (ray);
}

t_coor	ft_Yray(t_coor eqline, t_coor dir, t_coor ray, char **map)
{
	double eqsol;
	int midcase;

	midcase = 0;
	eqsol = (((int)ray.y + dir.y) - eqline.y) / eqline.x;
	eqsol = floor(eqsol * pow(10, 14) + 0.5) / pow(10, 14);
	if (dir.x == 0 && (ray.x == (double)((int)ray.x) ))//|| ray.y == (double)((int)ray.y)))
		midcase = -1;
	while ((eqsol < (int)ray.x + midcase + 1 && eqsol > (int)ray.x + midcase) ||
	(eqsol == (double)((int)eqsol)))
	{
		if (dir.x != -2)
			ray.x = eqsol;
		ray.y = (int)ray.y + dir.y;
		if (ft_ray_collision(map, ray, dir) == 1)
		{
			ray.dist = 0;
			return (ray);
		}
		if (dir.y == 0)
			dir.y = -1;
		eqsol = (((int)ray.y + dir.y) - eqline.y) / eqline.x;
		if (dir.x == 0 && ray.x == (double)((int)ray.x) ) //&& ray.x != (double)((int)ray.x)))
			midcase = -1;
		else
			midcase = 0;
	}
	ray.dist = 1;
	return (ray);
}

t_coor ft_vertical_ray(t_coor ray, t_coor dir, char **map)
{
	while (ft_ray_collision(map, ray, dir) != 1)
	{
		if (dir.y > 0)
			ray.y = (double)((int)ray.y + 1);
		else
		{
			if (ray.y == (double)((int)ray.y))
				ray.y = (double)((int)ray.y - 1);
			else
				ray.y = (double)((int)ray.y);
		}
	}
	return (ray);
}

t_coor	ft_ray(t_coor pos, t_coor dir, t_coor eqline, char **map)
{
	t_coor ray;

	ray.x = pos.x;
	ray.y = pos.y;
	ray.dist = -1;
//	printf("Ray fired! RayX = %f, RayY = %f\n", ray.x, ray.y);
	while (ray.x >= 0 && ray.y >= 0)
	{
		//printf("Calculating ray...\n");
		if (dir.x == -2)
		{
			ray = ft_vertical_ray(ray, dir, map);
			break;
		}
		ray = ft_Xray(eqline, dir, ray, map);
		if (ray.dist == 0)
			break;
		ray = ft_Yray(eqline, dir, ray, map);
		if (ray.dist == 0)
			break;
	}
	return (ray);
}

t_coor	ft_dirsteps(t_coor vecray)
{
	t_coor dir;

	if (vecray.x > 0)
		dir.x = 1;
	else if (vecray.x == 0)
		dir.x = -2;
	else
		dir.x = 0;
	if (vecray.y > 0)
		dir.y = 1;
	else
		dir.y = 0;
	return (dir);
}

t_coor	ft_raycannon(t_coor pos, t_coor vect, double angle, char **map)
{
	double pente;
	double x0;
	t_coor ray;
	t_coor vecray;
	t_coor dir;
	t_coor eqline;

//	printf("Cannon firing!\n");
	pente = 0;
	vecray.x = (vect.x * cos(angle)) - (vect.y * sin(angle));
	vecray.y = (vect.x * sin(angle)) + (vect.y * cos(angle));
	if (vecray.x != 0)
		pente = vecray.y / vecray.x;
	x0 =  pos.y - (pente * pos.x);
	eqline.x = pente;
	eqline.y = x0;
	dir = ft_dirsteps(vecray);
	ray = ft_ray(pos, dir, eqline, map);
	if (dir.x == -2)
		ray.dist = (ray.y - pos.y) < 0 ? -(ray.y - pos.y) : (ray.y - pos.y);
	else
		ray.dist = ft_pythagore((ray.x - pos.x), (ray.y - pos.y)) * cos(angle);
//	printf("Cannon Rearming!\n");
	return (ray);
}

void	ft_projection(t_game game, t_coor ray, int x, t_img *img)
{
	int		height;
	int		ncol;
	void	*test;
	double	distproj;
	t_coor	heightncol;

	distproj = ((double)(game.res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	heightncol.y = (double)(int)(distproj / ray.dist);
	//ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE; // Texture change avec distance
	heightncol.x = (double)x;
	if (ray.x == (double)((int)ray.x))
	{
		if (game.player.pos.x < ray.x)
		{
			heightncol.dist = (double)(((int)(game.WE.width * ray.y)) % game.WE.width);
			ft_drawcol(heightncol, game.WE, game, img);
		}
		else
		{
			heightncol.dist = (double)(((int)(game.EA.width * ray.y)) % game.EA.width);
			ft_drawcol(heightncol, game.EA, game, img);
		}
	}
	else
	{
		if (game.player.pos.y < ray.y)
		{
			heightncol.dist = (double)(((int)(game.NO.width * ray.x)) % game.NO.width);
			ft_drawcol(heightncol, game.NO, game, img);
		}
		else
		{
			heightncol.dist = (double)(((int)(game.SO.width * ray.x)) % game.SO.width);
			ft_drawcol(heightncol, game.SO, game, img);
		}
	}
	//printf("  ncol = %f\n", heightncol.dist);
	return ;
}

void	ft_raymachine(t_game game)
{
	int	x;
	double	angle;
	double	distproj;
	t_coor	ray;
	t_img	img;

//	printf("New Image!\n");
//	printf("PosX = %F, PosY =  %f, VectX = %f, VectY = %f\n", game.player.pos.x, game.player.pos.y, game.player.vect.x, game.player.vect.y);
//	printf("Pente = %f\n", game.player.vect.y/game.player.vect.x);
	x = 0;


	img.img_p = mlx_new_image(game.win.mlxp, game.res[0], game.res[1]);
	img.img = mlx_get_data_addr(img.img_p, &img.bpp, &img.s_line, &img.endian);
//	printf("Lines of size = %d, Total size = %d\n", img.s_line, img.s_line * game.res[1]);
	angle = (double)FOV / (double)game.res[0];
//	printf("Angle = %f, Distrproj =  %f", angle, distproj);
	while (x < game.res[0])
	{
		ray = ft_raycannon(game.player.pos, game.player.vect, 
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game.map);
		ft_projection(game, ray, x, &img);
		x++;
	}
	mlx_put_image_to_window(game.win.mlxp, game.win.winp, img.img_p, 0, 0);
	mlx_destroy_image(game.win.mlxp, img.img_p);
	return ;
}
