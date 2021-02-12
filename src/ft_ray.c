/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 20:10:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/12 01:45:18 by yotillar         ###   ########.fr       */
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

int	ft_vertical_sprite_col(t_coor sp, t_coor ray, t_img tex, t_coor pos)
{
	int col;
	t_coor a;
	double dist;
	double size;

	size = sp_size(tex.chr);
	a.x = ray.x;
	if (pos.y < sp.y)
		a.y = ray.y + 0.5;
	else
		a.y = ray.y - 0.5;
	dist = ft_pythagore(a.x - sp.x, a.y - sp.y);
	if (dist > size / 2)
		return (-1);
	if ((a.x < sp.x && pos.y >= sp.y) || (a.x > sp.x && pos.y <= sp.y) ||
	(a.y > sp.y && pos.x >= sp.x) || (a.y < sp.y && pos.x <= sp.x))
		col = (int)((double)tex.width * (((size / 2) - dist) / size));
	else if ((a.x > sp.x && pos.y >= sp.y) || (a.x < sp.x && pos.y <= sp.y) ||
	(a.y < sp.y && pos.x >= sp.x) || (a.y > sp.y && pos.x <= sp.x))
		col = (int)((double)tex.width * (((size / 2) + dist) / size));
	else if (a.x == sp.x && a.y == sp.y)
		col = (int)((double)tex.width * 0.5);
//	printf("!!DIST=%f;COL=%d;texwidth=%d!!\n!!sp.x=%f;sp.y=%f;a.x=%f;a.y=%f!!",eq2.dist, col, texwidth, sp.x, sp.y, a.x, a.y);
	return (col);
}

int	ft_sprite_col(t_coor sp, t_coor eqray, t_img tex, t_coor pos)
{
	int col;
	t_coor eq2;
	t_coor a;
	double size;

	size = sp_size(tex.chr);
	if (eqray.x > 0.000001 || eqray.x < -0.000001)
	{
		eq2.x = - (1.0 / eqray.x);
		eq2.y = sp.y - (eq2.x * sp.x);
		a.x = (eq2.y - eqray.y) / (eqray.x - eq2.x);
		a.y = (eq2.x * a.x) + eq2.y;
		eq2.dist = ft_pythagore(a.x - sp.x, a.y - sp.y);
	}
	else
	{
		a.x = sp.x;
		a.y = sp.y + (pos.y - sp.y);
		eq2.dist = fabs(pos.y - sp.y);
	}
	if (eq2.dist > size / 2)
		return (-1);
	if (((int)pos.x == (int)sp.x &&
	(a.x < sp.x && pos.y > sp.y || a.x > sp.x && pos.y < sp.y)) ||
	((int)pos.x != (int)sp.x && 
	(a.y > sp.y && pos.x > sp.x || a.y < sp.y && pos.x < sp.x)))
		col = (int)((double)tex.width * (((size / 2) - eq2.dist) / size));
	else if (((int)pos.x == (int)sp.x &&
	(a.x > sp.x && pos.y > sp.y || a.x < sp.x && pos.y < sp.y)) ||
	((int)pos.x != (int)sp.x &&
	(a.y < sp.y && pos.x > sp.x || a.y > sp.y && pos.x < sp.x)))
		col = (int)((double)tex.width * (((size / 2) + eq2.dist) / size));
	else if (a.x == sp.x && a.y == sp.y)
		col = (int)((double)tex.width * 0.5);
	//printf("!!DIST=%f;COL=%d;texwidth=%d!!\n!!sp.x=%f;sp.y=%f;a.x=%f;a.y=%f!!\n\n",eq2.dist, col, tex.width, sp.x, sp.y, eqray.x, a.y);
	return (col);
}

t_coor	ft_sprite_dist(char **map, t_coor ray, t_coor dir, t_coor pos)
{
	t_coor sp;
	int i;

	i = 0;
	if (ray.x == ((double)((int)ray.x)) && ray.y == ((double)((int)ray.y)))
	{
		if (dir.x <= 0)
			i = -1;
		if (dir.y <= 0)
			i = -1;
		sp.x = (int)ray.x + i + 0.5;
		sp.y = (int)ray.y + i + 0.5;
	}
	else if (ray.x == (double)((int)ray.x))
	{
		if (dir.x <= 0)
			i = -1;
		sp.x = (int)ray.x + i + 0.5;
		sp.y = (int)ray.y + 0.5;
	}
	else
	{
		if (dir.y <= 0)
			i = -1;
		sp.x = (int)ray.x + 0.5;
		sp.y = (int)ray.y + i + 0.5;
	}
	sp.dist = ft_pythagore(sp.y - pos.y, sp.x - pos.x);
	return (sp);
}

char	ft_ray_collision(char **map, t_coor ray, t_coor dir)
{
	int i;

	i = 0;
	if (ray.x == ((double)((int)ray.x)) && ray.y == ((double)((int)ray.y)))
	{
		if (dir.x <= 0)
			i = -1;
		if (dir.y <= 0)
			i = -1;
		if (map[(int)ray.y + i][(int)ray.x + i] != '0')
			return (map[(int)ray.y + i][(int)ray.x + i]);
	}
	else if (ray.x == (double)((int)ray.x))
	{
		if (dir.x <= 0)
			i = -1;
		//printf("RayX = %f, RayY = %f\n\n", ray.x, ray.y);
		if (map[(int)ray.y][(int)ray.x + i] != '0')
			return (map[(int)ray.y][(int)ray.x + i]);
	}
	else
	{
		if (dir.y <= 0)
			i = -1;
		if (map[(int)ray.y + i][(int)ray.x] != '0')
			return (map[(int)ray.y + i][(int)ray.x]);
	}
	return('0');
}

t_coor	*ft_add_door(t_game *game, t_coor ray, t_coor dir, t_coor eqline)
{
	t_coor *door;
	t_coor vect;
	int midcase;
	double eqsol;
	double distproj;
	t_img tex;

	door = (struct s_coor*)malloc(sizeof(struct s_coor));
	tex = find_sprite(game, ft_ray_collision(game->map, ray, dir));
	if (ray.dist == -4)
	{
		eqsol = ((int)ray.x +
		(game->player.pos.x < ray.x ? 0.5 : -0.5)) * eqline.x + eqline.y;
		eqsol = floor(eqsol * pow(10, 14) + 0.5) / pow(10, 14);
		if ((eqsol > (int)ray.y  && eqsol < (int)ray.y + 1))
		{
			door->x = (int)ray.x + (game->player.pos.x < ray.x ? 0.5 : -0.5);
			door->y = eqsol;
//			printf("door.y=%f\n", door->y);
		}
		else
			return (NULL);
	}
	else if (ray.dist == -5)
	{
		eqsol = (((int)ray.y +
		(game->player.pos.y < ray.y ? 0.5 : -0.5)) - eqline.y) / eqline.x;
		eqsol = floor(eqsol * pow(10, 14) + 0.5) / pow(10, 14);
		if ((eqsol < (int)ray.x + 1 && eqsol > (int)ray.x))
		{
			if (dir.x != -2)
				door->x = eqsol;
			door->y = (int)ray.y + (game->player.pos.y < ray.y ? 0.5 : -0.5);
//			printf("door.x=%f\n", door->x);
		}
		else
			return (NULL);
	}
	vect.x = game->player.pos.x - ray.x; ///////////////fonction calculer angle ?
	vect.y = game->player.pos.y - ray.y;
	vect.dist = (vect.x * game->player.vect.x) + (vect.y * game->player.vect.y);
	vect.dist = vect.dist / (ft_pythagore(vect.x, vect.y) *
	ft_pythagore(game->player.vect.x, game->player.vect.y));
	door->dist = fabs(vect.dist) * ft_pythagore(door->y - game->player.pos.y, 
	door->x - game->player.pos.x);
//	printf("door.x=%f\n", door->x);
	if (door->x == (double)((int)door->x + 0.5))
		door->x = (double)(((int)(tex.width * door->y)) % tex.width);
	else if (door->y == (double)((int)door->y + 0.5))
		door->x = (double)(((int)(tex.width * door->x)) % tex.width);
	distproj = ((double)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	door->y = round(distproj / door->dist);
//	printf("door.x=%f; door.y=%f\n", door->x, door->y);
	door->dist = (double)((int)ft_ray_collision(game->map, ray, dir));
	door->next = ray.next;
	return (door);
}

t_coor *ft_add_sprite(t_game *game, t_coor ray, t_coor dir, t_coor eqline)
{
	t_coor *sp;
	t_img tex;
	t_coor vect;
	t_coor tmp;
	double distproj;

	sp = (struct s_coor*)malloc(sizeof(struct s_coor));

	*sp = ft_sprite_dist(game->map, ray, dir, game->player.pos);
	tmp = *sp;
	tex = find_sprite(game, ft_ray_collision(game->map, ray, dir));
	vect.x = game->player.pos.x - sp->x;
	vect.y = game->player.pos.y - sp->y;
	vect.dist = (vect.x * game->player.vect.x) + (vect.y * game->player.vect.y);
	vect.dist = vect.dist / (ft_pythagore(vect.x, vect.y) *
	ft_pythagore(game->player.vect.x, game->player.vect.y));
	sp->dist = fabs(vect.dist) * sp->dist;
	if (ray.dist == -3)
		sp->x = (double)ft_vertical_sprite_col(*sp, ray, tex, game->player.pos);
	else
		sp->x = (double)ft_sprite_col(*sp, eqline, tex, game->player.pos);
	distproj = ((double)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	sp->y = round((distproj / sp->dist) * sp_size(tex.chr));
	sp->dist = ((double)((int)tmp.x) / 1000) + ((double)((int)tmp.y) / 1000000);
	sp->next = ray.next;
//	printf("&&&&sp.y=%f&&&&\n", sp->y);
	return (sp);
}

t_coor	ft_Xray(t_coor eqline, t_coor dir, t_coor ray, t_game *game)
{
	double eqsol;
	int midcase;
	t_coor *sp;

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
		if (ft_ray_collision(game->map, ray, dir) == '1')
		{
			ray.dist = -1;
			return (ray);
		}
		else if (ft_ray_collision(game->map, ray, dir) == 'P' ||
		ft_ray_collision(game->map, ray, dir) == 'p')
		{
			ray.dist = -4;
			sp = ft_add_door(game, ray, dir, eqline);
			if (sp != NULL)
				ray.next = sp;
		}
		else if (ft_ray_collision(game->map, ray, dir) != '0')
		{
			sp = ft_add_sprite(game, ray, dir, eqline);
			sp->dist = sp->dist + (double)((int)ft_ray_collision(game->map, ray, dir));
			//printf("SP=%f", sp->dist);
			if (sp->x != -1)
				ray.next = sp;
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

t_coor	ft_Yray(t_coor eqline, t_coor dir, t_coor ray, t_game *game)
{
	double eqsol;
	int midcase;
	t_coor *sp;

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
		if (ft_ray_collision(game->map, ray, dir) == '1')
		{
			ray.dist = -1;
			return (ray);
		}
		else if (ft_ray_collision(game->map, ray, dir) == 'P' ||
		ft_ray_collision(game->map, ray, dir) == 'p')
		{
			ray.dist = -5;
			sp = ft_add_door(game, ray, dir, eqline);
			if (sp != NULL)
				ray.next = sp;
		}
		else if (ft_ray_collision(game->map, ray, dir) != '0')
		{
			sp = ft_add_sprite(game, ray, dir, eqline);
			sp->dist = sp->dist + (double)((int)ft_ray_collision(game->map, ray, dir));
			if (sp->x != -1)
				ray.next = sp;
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

t_coor ft_vertical_ray(t_coor eqline, t_coor dir, t_coor ray, t_game *game)
{
	t_coor *sp;

	while (ft_ray_collision(game->map, ray, dir) != '1')
	{
		if (ft_ray_collision(game->map, ray, dir) != '1' &&
		ft_ray_collision(game->map, ray, dir) != '0')
		{
			ray.dist = -3;
			sp = ft_add_sprite(game, ray, dir, eqline);
			sp->dist = sp->dist + (double)((int)ft_ray_collision(game->map, ray, dir));
			//printf("SP=%f", sp->dist);
			if (sp->x != -1)
				ray.next = sp;
		}
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

t_coor	ft_raycannon(t_coor pos, t_coor vect, double angle, t_game *game)
{
	double pente;
	double x0;
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
	double	distproj;
	t_coor	heightncol;

	distproj = ((double)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	heightncol.y = (double)(int)(distproj / ray.dist);
	//ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE; // Texture change avec distance
	heightncol.dist = (double)x;
	heightncol.next = ray.next;
	if (ray.x == (double)((int)ray.x))
	{
		if (game->player.pos.x < ray.x)
		{
			heightncol.x = (double)(((int)(game->WE.width * ray.y)) % game->WE.width);
			ft_drawcol(&heightncol, game->WE, game, img);
		}
		else
		{
			heightncol.x = (double)(((int)(game->EA.width * ray.y)) % game->EA.width);
			ft_drawcol(&heightncol, game->EA, game, img);
		}
	}
	else
	{
		if (game->player.pos.y < ray.y)
		{
			heightncol.x = (double)(((int)(game->NO.width * ray.x)) % game->NO.width);
			ft_drawcol(&heightncol, game->NO, game, img);
		}
		else
		{
			heightncol.x = (double)(((int)(game->SO.width * ray.x)) % game->SO.width);
			ft_drawcol(&heightncol, game->SO, game, img);
		}
	}
	//printf("  ncol = %f\n", heightncol.dist);
	return ;
}

void	ft_raymachine(t_game *game)
{
	int	x;
	double	angle;
	double	distproj;
	t_coor	ray;
	t_img	img;
	t_img	weapon;

//	printf("New Image!\n");
//	printf("PosX = %F, PosY =  %f, VectX = %f, VectY = %f\n", game.player.pos.x, game.player.pos.y, game.player.vect.x, game.player.vect.y);
//	printf("Pente = %f\n", game.player.vect.y/game.player.vect.x);
	x = 0;

	apply_mvmt(game);
	img.img_p = mlx_new_image(game->win.mlxp, game->res[0], game->res[1]);
	img.img = mlx_get_data_addr(img.img_p, &img.bpp, &img.s_line, &img.endian);
	draw_sky(game, &img);
	angle = (double)FOV / (double)game->res[0];
	while (x < game->res[0])
	{
		ray = ft_raycannon(game->player.pos, game->player.vect, 
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game);
		ft_projection(game, ray, x, &img);
		x++;
	}
	draw_life(game, &img);
	draw_weapon(game, &img, weapon_fire_animation(game, game->player.weapon));
	if (game->is_bmp == 0)
		mlx_put_image_to_window(game->win.mlxp, game->win.winp, img.img_p, 0, 0);
	else
		save(game, &img);
	mlx_destroy_image(game->win.mlxp, img.img_p);
	return ;
}
