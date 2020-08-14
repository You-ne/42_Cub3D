#include "../Cub3D.h"

t_coor	ft_ray(t_coor pos, t_coor dir, t_coor eqline, char **map)
{
	t_coor ray;

	ray.x = pos.x;
	ray.y = pos.y;
	while (map[(int)ray.y][(int)ray.x] == '0')
	{
		if (dir.x != -2 && (int)(((int)ray.x + dir.x) * eqline.x + eqline.y) 
		== (int)ray.y)
		{
			ray.x = (int)ray.x + dir.x;
			ray.y = ((int)ray.x + dir.x) * eqline.x + eqline.y;
			if (dir.x == 0)
				dir.x = - 1;
		}
		else
		{
			if (dir.x != -2)
				ray.x = ((int)ray.y + dir.y - eqline.y) / eqline.x;
			ray.y = (int)ray.y + dir.y;
			if (dir.y == 0)
				dir.y = -1;
		}
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
	ray.dist = sqrt(((ray.x - pos.x) * (ray.x - pos.x))  + 
	((ray.y - pos.y) * (ray.x - pos.x))) * cos(angle);
	return (ray);
}

void	ft_drawcol(t_win xserv, int i, int height, t_graph graph)
{
	int y;

	printf("Col n°%d, height %d\n", i, height); 
	y = 0;
	while(y < (graph.res[1]/2 + height/2))
	{
		if(y > (graph.res[1]/2 - height/2))
			mlx_pixel_put(xserv.mlxp, xserv.winp, i, y, 16777011); 
		y++;
	}
}

void	ft_projection(t_graph graph, t_coor ray, double distproj, t_win xserv, t_coor pos, int i)
{
	int height;
	int ncol;

	printf("Raydist: %f, Distproj: %f\n", ray.dist, distproj);
	height = (int)((CUB_SIZE / (CUB_SIZE * ray.dist)) * distproj);
	ncol = ((int)(CUB_SIZE * ray.dist)) % CUB_SIZE;
	if (ray.x == (double)((int)ray.x))
	{
		if (pos.x < ray.x)
			ft_drawcol(xserv, i, height, graph);
		else
			ft_drawcol(xserv, i, height, graph);
	}
	else
	{
		if (pos.y < ray.y)
			ft_drawcol(xserv, i, height, graph);
		else
			ft_drawcol(xserv, i, height, graph);
	}
	return ;
}

void	ft_raymachine(t_coor vect, t_graph graph, char **map)
{
	int i;
	double angle;
	double distproj;
	t_coor ray;

	i = 0;
	distproj = (graph.res[0] / 2) / tan(FOV / 2);
	angle = (double)FOV / (double)graph.res[0];
	printf("Vect: x= %f, y= %f && Pos: x= %f, y= %f\n", vect.x, vect.y, graph.pos.x, graph.pos.y);
	printf("FOV = %d, ResX = %d, ResY = %d, Angle: %f\n", FOV, graph.res[0], graph.res[1], angle);
	while (i < graph.res[0])
	{
		ray = ft_raycannon(graph.pos, vect, (angle * i) - (FOV / 2), map);
		ft_projection(graph, ray, distproj, graph.win, graph.pos, i);
		i++;
	}
	return ;
}
