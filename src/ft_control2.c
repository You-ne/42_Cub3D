/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 01:27:22 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 01:33:27 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	open_door(t_game *g)
{
	if (g->player.vect.x >= 0 &&
	g->map[(int)g->player.pos.y][(int)g->player.pos.x + 1] == 'P')
		change_map(g, (int)g->player.pos.x + 1, (int)g->player.pos.y, 'p');
	else if (g->player.vect.x < 0 &&
	g->map[(int)g->player.pos.y][(int)g->player.pos.x - 1] == 'P')
		change_map(g, (int)g->player.pos.x - 1, (int)g->player.pos.y, 'p');
	else if (g->player.vect.y >= 0 &&
	g->map[(int)g->player.pos.y + 1][(int)g->player.pos.x] == 'P')
		change_map(g, (int)g->player.pos.x, (int)g->player.pos.y + 1, 'p');
	else if (g->player.vect.y < 0 &&
	g->map[(int)g->player.pos.y - 1][(int)g->player.pos.x] == 'P')
		change_map(g, (int)g->player.pos.x, (int)g->player.pos.y - 1, 'p');
	else if (g->player.vect.x >= 0 &&
	g->map[(int)g->player.pos.y][(int)g->player.pos.x + 1] == 'p')
		change_map(g, (int)g->player.pos.x + 1, (int)g->player.pos.y, 'P');
	else if (g->player.vect.x < 0 &&
	g->map[(int)g->player.pos.y][(int)g->player.pos.x - 1] == 'p')
		change_map(g, (int)g->player.pos.x - 1, (int)g->player.pos.y, 'P');
	else if (g->player.vect.y >= 0 &&
	g->map[(int)g->player.pos.y + 1][(int)g->player.pos.x] == 'p')
		change_map(g, (int)g->player.pos.x, (int)g->player.pos.y + 1, 'P');
	else if (g->player.vect.y < 0 &&
	g->map[(int)g->player.pos.y - 1][(int)g->player.pos.x] == 'p')
		change_map(g, (int)g->player.pos.x, (int)g->player.pos.y - 1, 'P');
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

void	move(t_player *player, char **map, float speed, int frontnback)
{
	float pente;
	float angl;
	float x;
	float y;

	pente = player->vect.y / player->vect.x;
	angl = atanf(pente);
	if (frontnback == 1)
	{
		x = player->pos.x + (speed * cos(angl) * (player->vect.x < 0 ? -1 : 1));
		y = player->pos.y + (speed * sin(angl) * (player->vect.x < 0 ? -1 : 1));
	}
	else
	{
		x = player->pos.x + (speed * cos(angl + (M_PI / 2)) *
		(player->vect.x < 0 ? -1 : 1));
		y = player->pos.y + (speed * sin(angl + (M_PI / 2)) *
		(player->vect.x < 0 ? -1 : 1));
	}
	if (sp_collision((int)x, (int)y, map) == 0)
	{
		player->pos.x = x;
		player->pos.y = y;
	}
}

void	apply_mvmt(t_game *game)
{
	int		x;

	x = 0;
	(game->rot_left == 1) ? (rotation(&game->player.vect, (-ROT_SPEED))) : x--;
	(game->rot_right == 1) ? (rotation(&game->player.vect, ROT_SPEED)) : x--;
	(game->left == 1) ? move(&game->player, game->map, -STRAFE_SPEED, 0) : x++;
	(game->right == 1) ? move(&game->player, game->map, STRAFE_SPEED, 0) : x++;
	(game->up == 1) ? move(&game->player, game->map, FRONT_SPEED, 1) : x++;
	(game->down == 1) ? move(&game->player, game->map, -FRONT_SPEED, 1) : x++;
	if (game->sprint == 1 && game->up == 1)
		move(&game->player, game->map, SPRINT_SPEED, 1);
}
