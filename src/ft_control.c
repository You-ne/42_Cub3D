/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 01:32:55 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
		game->left = 0;
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
		game->left = 1;
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
	static int	nose_axis;
	int			zfov;

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
