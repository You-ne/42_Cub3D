/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 02:35:29 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/16 03:25:10 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

//int	ft_move(int key, t_game *game)

int	ft_rotate(int side, t_game *game)
{
	double	rot;
	int	rot_unit;

	rot_unit = 5;
	rot = rot_unit * (M_PI / 180);
	if (side == 1)
	{
		game->player.pos.x = (game->player.vect.x * cos(rot)) - (game->player.vect.y * sin(rot));
		game->player.pos.y = (game->player.vect.y * sin(rot)) + (game->player.vect.y * cos(rot));
	}
	if (side == -1)
	{
		game->player.pos.x = (game->player.vect.x * cos(-rot)) - (game->player.vect.y * sin(-rot));
		game->player.pos.y = (game->player.vect.y * sin(-rot)) + (game->player.vect.y * cos(-rot));
	}
}

int	keyboard(int key, t_game *game)
{
	printf("Key pressed!\n");
	if(key == ESC)
		ft_exit(game->win);
	if(key == UP || key == DOWN || key == Z || key == S || key == Q || key == D)
		ft_move(game);
	if(key == A || key == LEFT)
		ft_rotate(1, game);
	if(key == E || key == RIGHT)
		ft_rotate(-1, game);

	// do fire, sprint, pause
	return (0);
}
