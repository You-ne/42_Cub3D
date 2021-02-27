/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/27 03:44:43 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

void	move(t_player *player, char **map, float speed, int frontnback)
{
	float pente;
	float angle;
	float x;
	float y;


	pente = player->vect.y / player->vect.x;
	angle = atanf(pente);
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
	float x;
	float y;

	x = vect->x;
	y = vect->y;

	vect->x = (x * cos(angle)) - (y * sin(angle));
	vect->y = (x * sin(angle) + y * cos(angle));
}

void	open_door(t_game *game)
{
	if (game->player.vect.x >= 0 &&
	game->map[(int)game->player.pos.y][(int)game->player.pos.x + 1] == 'P')
		change_map(game, (int)game->player.pos.x + 1, (int)game->player.pos.y, 'p');
	else if (game->player.vect.x < 0 &&
	game->map[(int)game->player.pos.y][(int)game->player.pos.x - 1] == 'P')
		change_map(game, (int)game->player.pos.x - 1, (int)game->player.pos.y, 'p');
	else if (game->player.vect.y >= 0 &&
	game->map[(int)game->player.pos.y + 1][(int)game->player.pos.x] == 'P')
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y + 1, 'p');
	else if (game->player.vect.y < 0 &&
	game->map[(int)game->player.pos.y - 1][(int)game->player.pos.x] == 'P')
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y - 1, 'p');
	else if (game->player.vect.x >= 0 &&
	game->map[(int)game->player.pos.y][(int)game->player.pos.x + 1] == 'p')
		change_map(game, (int)game->player.pos.x + 1, (int)game->player.pos.y, 'P');
	else if (game->player.vect.x < 0 &&
	game->map[(int)game->player.pos.y][(int)game->player.pos.x - 1] == 'p')
		change_map(game, (int)game->player.pos.x - 1, (int)game->player.pos.y, 'P');
	else if (game->player.vect.y >= 0 &&
	game->map[(int)game->player.pos.y + 1][(int)game->player.pos.x] == 'p')
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y + 1, 'P');
	else if (game->player.vect.y < 0 &&
	game->map[(int)game->player.pos.y - 1][(int)game->player.pos.x] == 'p')
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y - 1, 'P');
}

void	key_release2(int keycode, t_game *game)
{
	if (keycode == Z)
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
	else if (keycode == SPACE)
		game->fire = 0;
	else if (keycode == T)
		open_door(game);
}

int		key_release(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_exit(keycode, game);
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
	key_release2(keycode, game);
}

void	key_press3(int keycode, t_game *game)
{
	static int i;

	if (keycode == SPACE)
	{
		if (i != 1)
			game->fire_t1 = clock();
		game->fire = 1;
		i = 1;
	}
	else
		i = 0;
}

void	key_press2(int keycode, t_game *game)
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
	key_press3(keycode, game);
}

int		key_press(int keycode, t_game *game)
{
	static int nose_axis;
	int zfov;

	zfov = (int)(((float)game->res[1] / (float)game->res[0]) * FOV);
	if (!nose_axis)
		nose_axis = 0;
	if (keycode == TC)
	{
		nose_axis = nose_axis - (int)((game->res[1] / zfov) * ZROT_SPEED);
		nose_axis = nose_axis < -game->res[1] ? -game->res[1] : nose_axis;
		game->tilt = nose_axis;
	}
	if (keycode == X)
	{
		nose_axis = nose_axis + (int)((game->res[1] / zfov) * ZROT_SPEED);
		nose_axis = nose_axis > game->res[1] ? game->res[1] : nose_axis;
		game->tilt = nose_axis;
	}
	key_press2(keycode, game);
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
