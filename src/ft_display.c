/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:44:36 by yotillar          #+#    #+#             */
/*   Updated: 2020/12/11 20:42:32 by yotillar         ###   ########.fr       */
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

void	ft_start_display(t_game game)
{

	printf("\nStarting X Server with resolution %dx%d\n\n", game.res[0], game.res[1]);

//pq en commnentaire?
//	game.win.mlxp = mlx_init();
//	game.win.winp = mlx_new_window(game.win.mlxp, game.res[0], game.res[1], "Cub3D");

	printf(GREEN);
	printf("\nStarting Raymachine.....\n\n");
	ft_raymachine(game);
	printf(RED);
	printf("\nStoping Raymachine.\n\n");

	printf(RESET);
	printf("Hooking...\n");
	mlx_hook(game.win.winp, 2, KEY_PRESS_M, &keyboard, &game);
	mlx_hook(game.win.winp, 3, KEY_RELEASE_M, &keyboard, &game);
	mlx_hook(game.win.winp, 17, (1L<<17), ft_exit, &game.win);
	//mlx_hook(xserv.winp, 4, BUTTON_PRESS_M, &mouse, &xserv);
	//mlx_hook(xserv.winp, 5, BUTTON_RELEASE_M, &mouse, &xserv);
	printf("\nXserv start looping, waiting for events:\n\n");
	mlx_loop(game.win.mlxp);
	printf("\nDisplay done!\n\n");
}
