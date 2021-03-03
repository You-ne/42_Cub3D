/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 02:50:54 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:08:54 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	game->sa->next = NULL;
	game->sa->chr = '0';
	game->sp->next = NULL;
	game->sp->chr = '0';
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
	game->fl = 0;
	game->ce = 0;
	game->res[0] = 0;
	game->res[1] = 0;
	game->win_created = 0;
	game->map_found = 0;
	game->map = NULL;
	game->secret.x = 0;
	game->secret.y = 0;
	game->secret.dist = 0;
	game->sky.img_p = NULL;
	if (!(game->sa = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	if (!(game->sp = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	game->player.num_weapon = 1;
	game->player.damage = -50;
	game->player.pv = 100.0;
	game->player.ammo = 30;
	game->player.fire = 0;
	game->start_found = 0;
	init_params(game);
	init_enemies(game);
}
