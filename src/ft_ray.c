

#include "../Cub3D.h"

double	ft_pythagore(double x, double y)
{
	double sqr;
	double dist;

	sqr = (x * x)  + (y * y);
	dist = sqrt(sqr);
	return (dist);
}

int	ft_collision(char **map, t_coor ray, t_coor dir)
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

	printf("X");
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
		if (ft_collision(map, ray, dir) == 1)
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
		if (ft_collision(map, ray, dir) == 1)
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
	while (ray.x >= 0 && ray.y >= 0)
	{
		if (dir.x == -2)
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
	ray.dist = ft_pythagore((ray.x - pos.x), (ray.y - pos.y)) * cos(angle);
	return (ray);
}

void	ft_drawcol(int i, int height, t_game game)
{
	int y;
	t_win	win;

	win = game.win;
	y = 0;
	while(y < (game.res[1]/2 + height/2))
	{
		if(y > (game.res[1]/2 - height/2))
			mlx_pixel_put(win.mlxp, win.winp, i, y, 16772864);
		y++;
	}
}

void	ft_projection(t_game game, t_coor ray, double distproj, int i)
{
	int height;
	int ncol;
	void	*test;
	double	pyth1;
	double	pyth2;

	pyth1 = ft_pythagore(distproj, (game.res[1] / 2));
	pyth2 = ft_pythagore(ray.dist, (CUB_SIZE / 2));
	height = CUB_SIZE * (pyth1 / pyth2);
	//height = (int)(distproj / ray.dist);
	ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE;
	if (ray.x == (double)((int)ray.x))
	{
		if (game.player.pos.x < ray.x)
			ft_drawcol(i, height, game);
		else
			ft_drawcol(i, height, game);
	}
	else
	{
		if (game.player.pos.y < ray.y)
			ft_drawcol(i, height, game);
		else
			ft_drawcol(i, height, game);
	}
	return ;
}

void	ft_raymachine(t_game game)
{
	int i;
	double angle;
	double distproj;
	t_coor ray;

	i = 0;
	distproj = ((double)(game.res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	angle = (double)FOV / game.res[0];
	while (i < game.res[0])
	{
		ray = ft_raycannon(game.player.pos, game.player.vect, 
		(M_PI / 180) * ((angle * i) - (FOV / 2)), game.map);
		ft_projection(game, ray, distproj, i);
		i++;
	}
	return ;
}

