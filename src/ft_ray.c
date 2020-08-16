

#include "../Cub3D.h"

int	ft_collision(char **map, t_coor ray, t_coor dir)
{
	int i;

	i = 0;
	printf("\nTESTWALL : rayx = %.16f ;; rayy = %.16f", ray.x, ray.y);
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
		printf("\ntestwally = %i ; testwallx = %i ", (int)ray.y + i, (int)ray.x);
		if (dir.x <= 0)
			i = -1;
		if (map[(int)ray.y][(int)ray.x + i] == '1')
			return (1);
	}
	else
	{
		if (dir.y <= 0)
			i = -1;
		printf("\ntestwally = %i ; testwallx = %i ", (int)ray.y + i, (int)ray.x);
		if (map[(int)ray.y + i][(int)ray.x] == '1')
		{
			return (1);
		}
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
	if (dir.y == 0 && ray.y == (double)((int)ray.y) && ray.x != (double)((int)ray.x))//////////////////////////)
		midcase = -1;
	printf("\nmidcase = %i, eqsol = %.16f, ray.y = %.16f, ray.x+dir = %.16f", midcase, eqsol, ray.y, (int)ray.x + dir.x);
	while ((eqsol > (int)ray.y + midcase && eqsol < (int)ray.y + midcase + 1) || 
	(eqsol == (int)eqsol))
	{
		printf("\n!V(x)!");
		ray.x = (int)ray.x + dir.x;
		ray.y = eqsol;
		printf("\nLimite1 = %i ; Limite2 %i; Eqsol = %.15f", (int)(ray.y) + midcase, (int)(ray.y) + midcase + 1, eqsol);
		printf("\nray.y = %.16f; ray.x %.16f; midcase = %i", ray.y, ray.x, midcase);
		if (ft_collision(map, ray, dir) == 1)
		{
			ray.dist = 0;
			return (ray);
		}
		if (dir.x == 0)
			dir.x = -1;
		eqsol = ((int)ray.x + dir.x) * eqline.x + eqline.y;
		if (dir.y == 0 && ray.y == (double)((int)ray.y) ) //&& ray.x != (double)((int)ray.x))//////////////////////////)
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
	printf("\nY");
	printf("\n ray.x = %.16f ; ray.y = %.16f", ray.x, ray.y);
	eqsol = (((int)ray.y + dir.y) - eqline.y) / eqline.x;
	eqsol = floor(eqsol * pow(10, 14) + 0.5) / pow(10, 14);
	if (dir.x == 0 && (ray.x == (double)((int)ray.x) ))//|| ray.y == (double)((int)ray.y)))
		midcase = -1;
	printf("\nround(ray.x) = %f, eqsol = %.16f, ray.x = %.16f, ray.y = %.16f", round(ray.x), eqsol, ray.x, (int)ray.y);
	while ((eqsol < (int)ray.x + midcase + 1 && eqsol > (int)ray.x + midcase) ||
	(eqsol == (double)((int)eqsol)))
	{
		printf("\n!H(y)!");
		if (dir.x != -2)
			ray.x = eqsol;
		ray.y = (int)ray.y + dir.y;
		printf("\nray.y = %.16f; ray.x %.16f");
		if (ft_collision(map, ray, dir) == 1)
		{
			ray.dist = 0;
			return (ray);
		}
		if (dir.y == 0)
			dir.y = -1;
		eqsol = (((int)ray.y + dir.y) - eqline.y) / eqline.x;
		if (dir.x == 0 && ray.x == (double)((int)ray.x) ) //&& ray.x != (double)((int)ray.x))//////////////////////////)
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
	printf("\n\n\n\n1111111111");
	while (ray.x >= 0 && ray.y >= 0)
	{
		printf("\n\n\n\n\n22");
		//if (dir.x == -2)
		ray = ft_Xray(eqline, dir, ray, map);
		if (ray.dist == 0)
			break;
		ray = ft_Yray(eqline, dir, ray, map);
		printf("\n(ExY) ray.x = %.16f ; ray.y = %.16f ", ray.x, ray.y);
		if (ray.dist == 0)
			break;
		//printf("\nRay.x = %f ; Ray.y = %f ", ray.x, ray.y);
	}
	//printf("\n\n\n\n\n3333");
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
	double sqrx;
	double sqry;
	double sqr;
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
	printf("\nRay.x = %.16f Ray.y = %.16f ", ray.x, ray.y);
	sqrx = ray.x - pos.x;
	sqry = ray.y - pos.y;
	sqr = (sqrx * sqrx)  + (sqry * sqry);
	ray.dist = sqrt(sqr) * cos(angle);
	printf("\nRayDist = %f ", ray.dist);
	return (ray);
}

void	ft_drawcol(int i, int height, t_game game)
{
	int y;
	t_win	win;

	printf("resx = %d, resy = %d\n", game.res[0], game.res[1]);
	win = game.win;
	y = 0;
	printf("I = %d, Y = %d Height = %d\n", i, y, height);
	printf("\nResult = %d\n", ((game.res[1]/2) + (height/2)));
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
	t_coor pos;
	void	*test;

	printf("Wall found\n");
	pos = game.player.pos;
	printf("\nray.dist = %f; distproj = ; %f", ray.dist, distproj);
	height = (int)(distproj / ray.dist);
	ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE;
	if (ray.x == (double)((int)ray.x))
	{
		if (pos.x < ray.x)
			ft_drawcol(i, height, game);
		else
			ft_drawcol(i, height, game);
	}
	else
	{
		if (pos.y < ray.y)
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
	printf("\n distproj = %f; game.res = %f; tan(FOV/2) = %f",  distproj, (double)game.res[0], tan(FOV/2));
	angle = (double)FOV / game.res[0];
	printf("FOV = %d, ResX = %d, Angle: %f\n", FOV, game.res[0],angle);
	while (i < game.res[0])
	{
		printf("angle%d = %.15f ", i, (angle * i) - (FOV / 2));
		ray = ft_raycannon(game.player.pos, game.player.vect, (M_PI / 180) * ((angle * i) - (FOV / 2)), game.map);
		ft_projection(game, ray, distproj, i);
		i++;
	}
	return ;
}

