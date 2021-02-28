/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 02:50:54 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 08:04:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	init_params(t_game *game)
{
	game->found[0] = 0;
	game->found[1] = 0;
	game->found[2] = 0;
	game->found[3] = 0;
	game->found[4] = 0;
	game->found[5] = 0;
	game->found[6] = 0;
	game->found[7] = 0;
}

void	init_enemies(t_game *game)
{
	if (!(game->enemies = (t_enemy*)malloc(sizeof(t_enemy))))
		ft_error("Malloc a échoué !\n", game);
	game->enemies->next = NULL;
	game->enemies->x = -1;
	game->enemies->chr = '0';
}

void	init_keys(t_game *game)
{
	game->up = 0;
	game->down = 0;
	game->left = 0;
	game->right = 0;
	game->rot_left = 0;
	game->rot_right = 0;
	game->map = NULL;
	game->sprint = 0;
	game->tilt = 0;
	game->fire = 0;
}

void	init(t_game *game)
{
	game->Fl = 0;
	game->Ce = 0;
	game->res[0] = 0;
	game->res[1] = 0;
	game->win_created = 0;
	game->map_found = 0;
	game->map = NULL;
	game->nb_params = 0;
	game->secret.x = 0;
	game->secret.y = 0;
	game->secret.dist = 0;
	if (!(game->SA = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	if (!(game->SP = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	game->SA->chr = '1';
	game->player.num_weapon = 1;
	game->player.damage = -50;
	game->player.pv = 100.0;
	game->player.ammo = 30;
	game->player.fire = 0;
	init_params(game);
	init_enemies(game);
}

void	init_screens(t_game *game)
{
	game->game_over.img_p = mlx_xpm_file_to_image(game->win.mlxp, GAME_OVER,
	&game->game_over.width, &game->game_over.height);
	game->game_over.img = mlx_get_data_addr(game->game_over.img_p,
	&game->game_over.bpp, &game->game_over.s_line, &game->game_over.endian);
	game->you_win.img_p = mlx_xpm_file_to_image(game->win.mlxp, YOU_WIN,
	&game->you_win.width, &game->you_win.height);
	game->you_win.img = mlx_get_data_addr(game->you_win.img_p,
	&game->you_win.bpp, &game->you_win.s_line, &game->you_win.endian);
	game->player.vect = init_dir(game->map, game->player.pos);
}
