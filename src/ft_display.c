/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 14:44:36 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/27 07:45:02 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		next_frame(t_game *game)
{
	t_img	img;
	t_enemy *enemy;
	clock_t t2;

	t2 = clock();
	img.img_p = mlx_new_image(game->win.mlxp, game->res[0], game->res[1]);
	img.img = mlx_get_data_addr(img.img_p, &img.bpp, &img.s_line, &img.endian);
	if (game->victory && (t2 - game->victory) / CLOCKS_PER_SEC > 10)
	{
		end_screen(game, &game->you_win, &img);
		mlx_put_image_to_window(game->win.mlxp, game->win.winp, img.img_p, 0, 0);
		mlx_destroy_image(game->win.mlxp, img.img_p);
	}
	else if (game->player.pv > 0)
	{
		sp_events(game);
		apply_mvmt(game);
		draw_sky(game, &img);
		ft_raymachine(game, &img);
		draw_life(game, &img);
		draw_weapon(game, &img, weapon_fire_animation(game, game->player.weapon));
		mlx_put_image_to_window(game->win.mlxp, game->win.winp, img.img_p, 0, 0);
		mlx_destroy_image(game->win.mlxp, img.img_p);
	}
	else
	{
		end_screen(game, &game->game_over, &img);
		mlx_put_image_to_window(game->win.mlxp, game->win.winp, img.img_p, 0, 0);
		mlx_destroy_image(game->win.mlxp, img.img_p);
	}
	return (0);
}

void	ft_start_bmp(t_game *game)
{
	t_img	img;

	img.img_p = mlx_new_image(game->win.mlxp, game->res[0], game->res[1]);
	img.img = mlx_get_data_addr(img.img_p, &img.bpp, &img.s_line, &img.endian);
	draw_sky(game, &img);
	ft_raymachine(game, &img);
	draw_life(game, &img);
	draw_weapon(game, &img, weapon_fire_animation(game, game->player.weapon));
	save(game, &img);
	mlx_destroy_image(game->win.mlxp, img.img_p);
	ft_exit(65307, game);
}

void	ft_start_display(t_game game)
{
	printf("\nStarting X Server with resolution %dx%d\n\n", game.res[0], game.res[1]);
	if (game.is_bmp == 0)
	{
		game.win.winp = mlx_new_window(game.win.mlxp, game.res[0], game.res[1], "Cub3D");
		printf(GREEN);
		printf("\nStarting Raymachine.....\n\n");
//		ft_raymachine(&game);
		printf(RESET);
		printf("Hooking...\n\n");
		mlx_hook(game.win.winp, 2, KEY_PRESS_M, key_press, &game);
		mlx_hook(game.win.winp, 3, KEY_RELEASE_M, key_release, &game);
		mlx_hook(game.win.winp, 17, (1L<<17), ft_exit, &game);
		printf("%.2f PV\n\n", game.player.pv);
		mlx_loop_hook(game.win.mlxp, next_frame, &game);
		mlx_loop(game.win.mlxp);
		printf("\nXserv start looping, waiting for events:\n\n");
		printf("\nDisplay done!\n\n");
	}
	else if (game.is_bmp == 1)
		ft_start_bmp(&game);
}
