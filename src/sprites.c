/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:27:58 by antoine           #+#    #+#             */
/*   Updated: 2021/02/22 10:58:27 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	ft_calc_col_sprite(t_coor *a, t_coor *pos, t_coor *sp, t_img *tex)
{
	float s;

	s = sp_size(tex->chr);
	if (a->x == sp->x && a->y == sp->y)
		return ((int)((float)tex->width * 0.5));
	else if ((int)pos->x > (int)sp->x)
	{
		return (a->y > sp->y ? (int)((float)tex->width * (((s / 2) - pos->dist)
		/ s)) : (int)((float)tex->width * (((s / 2) + pos->dist) / s)));
	}
	else if ((int)pos->x < (int)sp->x)
	{
		return (a->y < sp->y ? (int)((float)tex->width * (((s / 2) - pos->dist)
		/ s)) : (int)((float)tex->width * (((s / 2) + pos->dist) / s)));
	}
	else if ((int)pos->y > (int)sp->y)
	{
		return (a->x < sp->x ? (int)((float)tex->width * (((s / 2) - pos->dist)
		/ s)) : (int)((float)tex->width * (((s / 2) + pos->dist) / s)));
	}
	else if ((int)pos->y < (int)sp->y)
	{
		return (a->x > sp->x ? (int)((float)tex->width * (((s / 2) - pos->dist)
		/ s)) : (int)((float)tex->width * (((s / 2) + pos->dist) / s)));
	}
}

int	ft_vertical_sprite_col(t_coor *sp, t_coor *ray, t_img *tex, t_coor *pos)
{
	int col;
	t_coor a;
	float dist;
	float size;

	size = sp_size(tex->chr);
	a.x = ray->x;
	if (pos->y < sp->y)
		a.y = ray->y + 0.5;
	else
		a.y = ray->y - 0.5;
	dist = ft_pythagore(a.x - sp->x, a.y - sp->y);
	if (dist > size / 2)
		return (-1);
	pos->dist = dist;
	col = ft_calc_col_sprite(&a, pos, sp, tex);
	return (col);
}

int	ft_sprite_col(t_coor *sp, t_coor *eqray, t_img *tex, t_coor *pos)
{
	int col;
	t_coor eq2;
	t_coor a;
	float size;

	size = sp_size(tex->chr);
	if (eqray->x > 0.0005 || eqray->x < -0.0005)
	{
		eq2.x = - (1.0 / eqray->x);
		eq2.y = sp->y - (eq2.x * sp->x);
		a.x = (eq2.y - eqray->y) / (eqray->x - eq2.x);
		a.y = (eq2.x * a.x) + eq2.y;
		eq2.dist = ft_pythagore(a.x - sp->x, a.y - sp->y);
	}
	else
	{
		a.x = sp->x;
		a.y = pos->y;
		eq2.dist = fabs(a.y - sp->y) + (fabs(a.y - sp->y) / 70);
	}
	if (eq2.dist > size / 2)
		return (-1);
	pos->dist = eq2.dist;
	col = ft_calc_col_sprite(&a, pos, sp, tex);
	return (col);
}

t_coor	ft_sprite_dist(char **map, t_coor *ray, t_coor *dir, t_coor *pos)
{
	t_coor sp;
	int i;

	i = 0;
	if (ray->x == ((float)((int)ray->x)) && ray->y == ((float)((int)ray->y)))
	{
		i = (dir->x <= 0) ? -1 : i;
		i = (dir->y <= 0) ? -1 : i;
		sp.x = (int)ray->x + i + 0.5;
		sp.y = (int)ray->y + i + 0.5;
	}
	else if (ray->x == (float)((int)ray->x))
	{
		i = (dir->x <= 0) ? -1 : i;
		sp.x = (int)ray->x + i + 0.5;
		sp.y = (int)ray->y + 0.5;
	}
	else
	{
		i = (dir->y <= 0) ? -1 : i;
		sp.x = (int)ray->x + 0.5;
		sp.y = (int)ray->y + i + 0.5;
	}
	sp.dist = ft_pythagore(sp.y - pos->y, sp.x - pos->x);
	return (sp);
}


t_coor *ft_add_sprite(t_game *game, t_coor *ray, t_coor *dir, t_coor *eqline)
{
	t_coor *sp;
	t_img tex;
	t_coor vect;
	t_coor *tmp;
	float distproj;

	sp = (struct s_coor*)malloc(sizeof(struct s_coor));

	*sp = ft_sprite_dist(game->map, ray, dir, &game->player.pos);
	tmp = sp;
	tex = find_sprite(game, ft_ray_collision(game->map, ray, dir));
	vect.x = game->player.pos.x - sp->x;
	vect.y = game->player.pos.y - sp->y;
	vect.dist = (vect.x * game->player.vect.x) + (vect.y * game->player.vect.y);
	vect.dist = vect.dist / (ft_pythagore(vect.x, vect.y) *
	ft_pythagore(game->player.vect.x, game->player.vect.y));
	sp->dist = fabs(vect.dist) * sp->dist;
	sp->x = (ray->dist == -3) ? (float)ft_vertical_sprite_col(sp, ray, &tex,
	&game->player.pos) : (float)ft_sprite_col(sp, eqline, &tex,
	&game->player.pos);
	distproj = ((float)(game->res[0]) / 2) / tan((M_PI / 180) * (FOV / 2));
	sp->y = roundf((distproj / sp->dist) * sp_size(tex.chr));
	sp->dist = ((float)((int)tmp->x) / 1000) + ((float)((int)tmp->y) / 1000000);
	sp->next = ray->next;
	return (sp);
}





