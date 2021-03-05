/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 01:27:22 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/02 21:42:07 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	open_door(t_game *g)
{
	t_coor *p;

	p = &g->player.pos;
	if (g->player.vect.x >= 0 && g->map[(int)p->y][(int)p->x + 1] == 'P')
		change_map(g, (int)p->x + 1, (int)p->y, 'p');
	else if (g->player.vect.x < 0 && g->map[(int)p->y][(int)p->x - 1] == 'P')
		change_map(g, (int)p->x - 1, (int)p->y, 'p');
	else if (g->player.vect.y >= 0 && g->map[(int)p->y + 1][(int)p->x] == 'P')
		change_map(g, (int)p->x, (int)p->y + 1, 'p');
	else if (g->player.vect.y < 0 && g->map[(int)p->y - 1][(int)p->x] == 'P')
		change_map(g, (int)p->x, (int)p->y - 1, 'p');
	else if (g->player.vect.x >= 0 && g->map[(int)p->y][(int)p->x + 1] == 'p')
		change_map(g, (int)p->x + 1, (int)p->y, 'P');
	else if (g->player.vect.x < 0 && g->map[(int)p->y][(int)p->x - 1] == 'p')
		change_map(g, (int)p->x - 1, (int)p->y, 'P');
	else if (g->player.vect.y >= 0 && g->map[(int)p->y + 1][(int)p->x] == 'p')
		change_map(g, (int)p->x, (int)p->y + 1, 'P');
	else if (g->player.vect.y < 0 && g->map[(int)p->y - 1][(int)p->x] == 'p')
		change_map(g, (int)p->x, (int)p->y - 1, 'P');
	else
		return ;
	if (system("aplay -N -q ./cont/sounds/door.wav &") == -1)
		ft_error("Erreur: aplay a échoué ! \n", g);
}

void	rotation(t_coor *vect, float angle)
{
	float x;
	float y;

	x = vect->x;
	y = vect->y;
	vect->x = (x * cos(angle)) - (y * sin(angle));
	vect->y = (x * sin(angle) + y * cos(angle));
}

void	move(t_game *g, float v, int frontnback)
{
	float pente;
	float angl;
	float x;
	float y;

	pente = g->player.vect.y / g->player.vect.x;
	angl = atanf(pente);
	if (frontnback == 1)
	{
		x = g->player.pos.x + (v * cos(angl) * (g->player.vect.x < 0 ? -1 : 1));
		y = g->player.pos.y + (v * sin(angl) * (g->player.vect.x < 0 ? -1 : 1));
	}
	else
	{
		x = g->player.pos.x + (v * cos(angl + (M_PI / 2)) *
		(g->player.vect.x < 0 ? -1 : 1));
		y = g->player.pos.y + (v * sin(angl + (M_PI / 2)) *
		(g->player.vect.x < 0 ? -1 : 1));
	}
	if (sp_collision((int)x, (int)y, g) == 0)
	{
		g->player.pos.x = x;
		g->player.pos.y = y;
	}
}

void	apply_mvmt(t_game *game)
{
	int		x;

	x = 0;
	if (game->sprint == 1 && game->up == 1)
		move(game, SPRINT_SPEED, 1);
	(game->rot_left == 1) ? (rotation(&game->player.vect, (-ROT_SPEED))) : x--;
	(game->rot_right == 1) ? (rotation(&game->player.vect, ROT_SPEED)) : x--;
	(game->left == 1) ? move(game, -STRAFE_SPEED, 0) : x++;
	(game->right == 1) ? move(game, STRAFE_SPEED, 0) : x++;
	(game->up == 1) ? move(game, FRONT_SPEED, 1) : x++;
	(game->down == 1) ? move(game, -FRONT_SPEED, 1) : x++;
}
