/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/03 21:41:36 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"
/*
int	ft_player_collision(int key, t_coor pos, t_coor vect, char **map)
{
	if (((int)pos.x + 0.05 > pos.x) && map[(int)pos.y][(int)round(pos.x) - 1] == '1')
	{
		if (vect.x < 0 && (((key == UP || key == Z) && (vect.x >= 0)) || 
	((key == DOWN || key == S) && (vect.x < 0))))
			return (1);
		if (vect.x > 0 && (((key == UP || key == Z) && (vect.x < 0)) || 
	((key == DOWN || key == S) && (vect.x >= 0))))
			return (1);
	}
	if (((int)pos.x + (1 - 0.05) < pos.x) && map[(int)pos.y][(int)round(pos.x)] == '1')
	{
		if (vect.x > 0 && (((key == UP || key == Z) && (vect.x >= 0)) || 
	((key == DOWN || key == S) && (vect.x < 0))))
			return (1);
		if (vect.x < 0 && (((key == UP || key == Z) && (vect.x < 0)) || 
	((key == DOWN || key == S) && (vect.x >= 0))))
			return (1);
	}
	if (((int)pos.y + 0.05 > pos.y) && map[(int)round(pos.y) - 1][(int)pos.x] == '1')
	{
		if (vect.y < 0 && (((key == UP || key == Z) && (vect.x >= 0)) || 
	((key == DOWN || key == S) && (vect.x < 0))))
			return (1);
		if (vect.y > 0 && (((key == UP || key == Z) && (vect.x < 0)) || 
	((key == DOWN || key == S) && (vect.x >= 0))))
			return (1);
	}
	if (((int)pos.y + (1 - 0.05) < pos.y) && map[(int)round(pos.y)][(int)pos.x] == '1')
	{
		if (vect.y > 0 && (((key == UP || key == Z) && (vect.x >= 0)) || 
	((key == DOWN || key == S) && (vect.x < 0))))
			return (1);
		if (vect.y < 0 && (((key == UP || key == Z) && (vect.x < 0)) || 
	((key == DOWN || key == S) && (vect.x >= 0))))
			return (1);

	}
	return (0);
}
*/

void	move(t_player *player, char **map, float speed, int frontnback)
{
	double pente;
	double angle;
	float x;
	float y;


	pente = player->vect.y / player->vect.x;
	angle = atan(pente);
	if (frontnback == 1)
	{
		x = player->pos.x + (speed * cos(angle) * (player->vect.x < 0 ? -1 : 1));
		y = player->pos.y + (speed * sin(angle) * (player->vect.x < 0 ? -1 : 1));
	}
	else
	{
		x = player->pos.x + (speed * cos(angle + (M_PI / 2)) * 
		(player->vect.x < 0 ? -1 : 1));
		y = player->pos.y + (speed * sin(angle + (M_PI / 2)) * 
		(player->vect.x < 0 ? -1 : 1));
	}
	if (sp_collision((int)x, (int)y, map) == 0)
	{
		player->pos.x = x;
		player->pos.y = y;
	}
}

void	rotation(t_coor *vect, float angle)
{
	double x;
	double y;

	x = vect->x;
	y = vect->y;

	vect->x = (x * cos(angle)) - (y * sin(angle));
	vect->y = (x * sin(angle) + y * cos(angle));
}

int		key_release(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(&game->win);
	else if (keycode == LEFT)
		game->left  = 0;
	else if (keycode == UP)
		game->up = 0;
	else if (keycode == RIGHT)
		game->right = 0;
	else if (keycode == DOWN)
		game->down = 0;
	else if (keycode == SHIFT_R)
		game->sprint = 0;
	else if (keycode == Z)
		game->up = 0;
	else if (keycode == A)
		game->left = 0;
	else if (keycode == S)
		game->down = 0;
	else if (keycode == D)
		game->right = 0;
	else if (keycode == Q)
		game->rot_left = 0;
	else if (keycode == E)
		game->rot_right = 0;
}

int		key_press(int keycode, t_game *game)
{
	if (keycode == LEFT)
		game->left  = 1;
	else if (keycode == UP)
		game->up = 1;
	else if (keycode == RIGHT)
		game->right = 1;
	else if (keycode == DOWN)
		game->down = 1;
	else if (keycode == SHIFT_R)
		game->sprint = 1;
	else if (keycode == Z)
		game->up = 1;
	else if (keycode == A)
		game->left = 1;
	else if (keycode == S)
		game->down = 1;
	else if (keycode == D)
		game->right = 1;
	else if (keycode == Q)
		game->rot_left = 1;
	else if (keycode == E)
		game->rot_right = 1;
}

void	apply_mvmt(t_game *game)
{
	int		bud;

	bud = 0;
	(game->rot_left == 1) ? (rotation(&game->player.vect, (-ROT_SPEED))) : bud--;
	(game->rot_right == 1) ? (rotation(&game->player.vect, ROT_SPEED)) : bud--;
	(game->left == 1) ? move(&game->player, game->map, -STRAFE_SPEED, 0) : bud++;
	(game->right == 1) ? move(&game->player, game->map, STRAFE_SPEED, 0) : bud++;
	(game->up == 1) ? move(&game->player, game->map, FRONT_SPEED, 1) : bud++;
	(game->down == 1) ? move(&game->player, game->map, -FRONT_SPEED, 1) : bud++;
	if (game->sprint == 1 && game->up == 1)
		move(&game->player, game->map, SPRINT_SPEED, 1);
}
