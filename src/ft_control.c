/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/16 07:01:10 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"
int	ft_move(int key, t_game *game)
{
	
}

int	ft_rotate(int side, t_game *game)
{
	double	rot;

	rot = ROT_SPEED * (M_PI / 180);
	if (side == 1)
	{
		game->player.vect.x = (game->player.vect.x * cos(rot)) - (game->player.vect.y * sin(rot));
		game->player.vect.y = (game->player.vect.x * sin(rot)) + (game->player.vect.y * cos(rot));
		printf("Rotating %d degrees\n", ROT_SPEED);
	}
	if (side == -1)
	{
		game->player.vect.x = (game->player.vect.x * cos(-1 * rot)) - (game->player.vect.y * sin(-1 * rot));
		game->player.vect.y = (game->player.vect.x * sin(-1 * rot)) + (game->player.vect.y * cos(-1 * rot));
		printf("Rotating %d degrees\n", -ROT_SPEED);
	}
//	mlx_clear_window(game->win.mlxp, game->win.winp);
	ft_raymachine(*game);
	return (0);
}

int	keyboard(int key, t_game *game)
{
	printf("\nKey pressed!\n\n");
	if(key == ESC)
		ft_exit(&game->win);
/*	if(key == UP || key == DOWN || key == Z || key == S || key == Q || key == D)
		ft_move(game);*/

	if(key == A || key == LEFT)
		ft_rotate(1, game);
	if(key == E || key == RIGHT)
		ft_rotate(-1, game);
/*	printf("Pos X2 = %f, Pos Y2 = %f\n", game->player.pos.x, game->player.pos.y);
	printf("Vect X2 = %f, Vect Y2 = %f\n\n", game->player.vect.x, game->player.vect.y);*/
	if(key == A || key == LEFT)
	// do fire, sprint, pause
	return (0);
}
