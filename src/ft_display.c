/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:44:36 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/16 01:20:12 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

//int	redraw(void* win) mettre images en tampon
int	ft_exit(t_win *win)
{
	printf("\nExit attempt. \n");
	mlx_destroy_window(win->mlxp, win->winp);
	printf(RED);
	printf("Window closed\n");
	printf(RESET);
	exit(0);
	return(0);
}

int	keyboard(int key, t_win *win)
{
	printf("Key pressed!\n");
/*	if (win == NULL)
		printf("Win dont exist\n");*/
	if(key == ESC)
		ft_exit(win);
	return (0);
}

//change param pour prendre *game)
void	ft_start_display(t_game game, char **map)
{

	printf("\nStarting X Server with resolution %dx%d\n\n", game.res[0], game.res[1]);

	game.win.mlxp = mlx_init();
	game.win.winp = mlx_new_window(game.win.mlxp, game.res[0], game.res[1], "Cub3D");

	printf(GREEN);
	printf("\nStarting Raymachine.....\n\n");
	ft_raymachine(game, map);
	printf(RED);
	printf("\nStoping Raymachine.\n\n");

	printf(RESET);
	printf("Hooking...\n");
	mlx_hook(game.win.winp, 2, KEY_PRESS_M, &keyboard, &game.win);
	mlx_hook(game.win.winp, 3, KEY_RELEASE_M, &keyboard, &game.win);
	//mlx_hook(xserv.winp, 4, BUTTON_PRESS_M, &mouse, &xserv);
	//mlx_hook(xserv.winp, 5, BUTTON_RELEASE_M, &mouse, &xserv);
	printf("\nXserv start looping, waiting for events:\n\n");
	mlx_loop(game.win.mlxp);
	printf("\nDisplay done!\n\n");
}
