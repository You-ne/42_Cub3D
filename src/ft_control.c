/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/03 00:07:42 by yotillar         ###   ########.fr       */
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
/*
int	ft_move(int key, t_game *game)
{
	double pente;
	double angle;
	double speed;

	pente = game->player.vect.y / game->player.vect.x;
	angle = atan(pente);
	if (key == UP || key == Z)
		speed = FRONT_SPEED;
	else if (key == DOWN || key == S)
		speed = BACK_SPEED;
	if (ft_player_collision(key, game->player.pos, game->player.vect, game->map) == 1)
		speed = 0;
	if (((key == UP || key == Z) && (game->player.vect.x >= 0)) || 
	((key == DOWN || key == S) && (game->player.vect.x < 0)))
	{
		game->player.pos.x = game->player.pos.x + (speed * cos(angle));
		game->player.pos.y = game->player.pos.y + (speed * sin(angle));
	}
	if (((key == UP || key == Z) && (game->player.vect.x < 0)) || 
	((key == DOWN || key == S) && (game->player.vect.x >= 0)))
	{
		game->player.pos.x = game->player.pos.x - (speed * cos(angle));
		game->player.pos.y = game->player.pos.y - (BACK_SPEED * sin(angle));
	}
	if (key == D) //&& (game->player.vect.y >= 0)) || 
//	(key == SHIFT_R && (g)))
	{
	//printf("test bug pas lateral");
		game->player.pos.x = game->player.pos.x + (STRAFE_SPEED * cos(angle +
		(M_PI / 2)));
		game->player.pos.y = game->player.pos.y + (STRAFE_SPEED * sin(angle +
		(M_PI / 2)));
	}
	if (key == SHIFT_R || key == A)// && (game->player.vect.y < 0)) || 
//	(key == SHIFT_R && (game->player.vect.y >= 0)))
	{
		game->player.pos.x = game->player.pos.x - (STRAFE_SPEED * cos(angle + 
		(M_PI / 2)));
		game->player.pos.y = game->player.pos.y - (STRAFE_SPEED * sin(angle + 
		(M_PI / 2)));
	}
	//printf("\nAngle = %f", angle);
//	mlx_clear_window(game->win.mlxp, game->win.winp);
	ft_raymachine(*game);
	return(0);
}

int	ft_rotate(int side, t_game *game)
{
	double	rot;

	rot = ROT_SPEED * (M_PI / 180);
	if (side == 1)
	{
		game->player.vect.x = (game->player.vect.x * cos(rot)) - (game->player.vect.y * sin(rot));
		game->player.vect.y = (game->player.vect.x * sin(rot)) + (game->player.vect.y * cos(rot));
	//	printf("Rotating %d degrees\n", ROT_SPEED);
	}
	if (side == -1)
	{
		game->player.vect.x = (game->player.vect.x * cos(-1 * rot)) - (game->player.vect.y * sin(-1 * rot));
		game->player.vect.y = (game->player.vect.x * sin(-1 * rot)) + (game->player.vect.y * cos(-1 * rot));
	//	printf("Rotating %d degrees\n", -ROT_SPEED);
	}
//	mlx_clear_window(game->win.mlxp, game->win.winp);
	ft_raymachine(*game);
	return (0);
}
*/
/*
int	keyboard(int key, t_game *game)
{
	//printf("\nKey pressed!\n\n");
	if(key == ESC)
		ft_exit(&game->win);
	if(key == UP || key == DOWN || key == Z || key == S || key == A 
	|| key == D || SHIFT_R || PAGE_DOWN)
		ft_move(key, game);

	if(key == Q || key == LEFT)
		ft_rotate(-1, game);
	if(key == E || key == RIGHT)
		ft_rotate(1, game);
	printf("Pos X2 = %f, Pos Y2 = %f\n", game->player.pos.x, game->player.pos.y);
	printf("Vect X2 = %f, Vect Y2 = %f\n\n", game->player.vect.x, game->player.vect.y);
	if(key == A || key == LEFT)
	// do fire, sprint, pause
	return (0);
}
*/

void	rotating(t_coor *vect, float angle)
{
	double x;
	double y;

	x = vect->x;
	y = vect->y;
	
	printf("Angle= %f\n", angle);
	printf("X= %f, Y= %f\n\n", vect->x, vect->y);
	vect->x = (x * cos(angle)) - (y * sin(angle));
	vect->y = (x * sin(angle) + y * cos(angle));
	printf("X2= %f, float angle)Y2= %f\n\n", vect->x, vect->y);
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
	(game->rot_left == 1) ? (rotating(&game->player.vect, (ROT_SPEED * -1))) : bud--;
	(game->rot_right == 1) ? (rotating(&game->player.vect, ROT_SPEED)) : bud--;
	/*(game_sprint == 1) ? : bud--;
	(game_left == 1) ? : bud--;
	(game_right == 1) ? : bud--;
	(game_up == 1) ? : bud++;
	(game_down == 1) ? : bud--;*/
}
