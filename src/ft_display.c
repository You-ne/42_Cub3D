/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:44:36 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/02 22:57:26 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		ft_exit(t_win *win)
{
	printf("\nExit attempt. \n");
	mlx_destroy_window(win->mlxp, win->winp);
	printf(RED);
	printf("Window closed\n");
	printf(RESET);
	exit(0);
	return(0);
}

int		next_frame(t_game *game)
{
	//cleaning?
	ft_raymachine(game);
	//image management?
	return (0);
}

void	ft_start_display(t_game game)
{

	printf("\nStarting X Server with resolution %dx%d\n\n", game.res[0], game.res[1]);
	printf(GREEN);
	printf("\nStarting Raymachine.....\n\n");
	ft_raymachine(&game);
	printf(RESET);
	printf("Hooking...\n");
	
	mlx_hook(game.win.winp, 2, KEY_PRESS_M, key_press, &game);
	mlx_hook(game.win.winp, 3, KEY_RELEASE_M, key_release, &game);
	mlx_hook(game.win.winp, 17, (1L<<17), ft_exit, &game.win);
	mlx_loop_hook(game.win.mlxp, next_frame, &game);
	mlx_loop(game.win.mlxp);
	printf("\nXserv start looping, waiting for events:\n\n");
	printf("\nDisplay done!\n\n");
}
