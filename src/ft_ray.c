

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

t_coor	ft_ray(t_coor pos, t_coor dir, t_coor eqline, char **map)
{
	t_coor ray;

	ray.x = pos.x;
	ray.y = pos.y;
//	printf("Ray fired! RayX = %f, RayY = %f\n", ray.x, ray.y);
	while (ray.x >= 0 && ray.y >= 0)
	{
		//printf("Calculating ray...\n");
	//	if (dir.x == -2)
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
		ray.dist = abs(ray.y - pos.y);//////marche pas
	else
		ray.dist = ft_pythagore((ray.x - pos.x), (ray.y - pos.y)) * cos(angle);
//	printf("Cannon Rearming!\n");
	return (ray);
}
void	ft_projection(t_game game, t_coor ray, double distproj, int x, t_img *img)
{
	int height;
	int ncol;
	void	*test;

	height = (int)(distproj / ray.dist);
	if (height > game.res[1])
		height = game.res[1];
	ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE; // Pour texture
	if (ray.x == (double)((int)ray.x))
	{
		if (game.player.pos.x < ray.x)
			ft_drawcol(x, height, game, img);
		else
			ft_drawcol(x, height, game, img);
	}
	else
	{
		if (game.player.pos.y < ray.y)
			ft_drawcol(x, height, game, img);
		else
			ft_drawcol(x, height, game, img);
	}
	//printf("Old Height = %d, New Height = %d\n", oldheight, height);
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
	distproj = ((double)(game.res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	angle = (double)FOV / (double)game.res[0];
//	printf("Angle = %f, Distrproj =  %f", angle, distproj);
	while (x < game.res[0])
	{
		ray = ft_raycannon(game.player.pos, game.player.vect, 
		(M_PI / 180) * ((angle * x) - (FOV / 2)), game.map);
		ft_projection(game, ray, distproj, x, &img);
		x++;
	}
	mlx_put_image_to_window(game.win.mlxp, game.win.winp, img.img_p, 0, 0);
	mlx_destroy_image(game.win.mlxp, img.img_p);
	return ;
}
