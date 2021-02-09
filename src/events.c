/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/09 02:10:52 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	weapon_fire(t_game *game)
{
	t_coor	tir;

	tir = ft_raycannon(game->player.pos, game->player.vect, 0.0, game);
	if (tir.next != NULL)
	{
		while (tir.next != NULL)
			tir = *tir.next;
		if ((char)((int)tir.dist) != '5')
			return ;
		tir.dist = (tir.dist - (int)tir.dist) * 1000.0;
		tir.x = (int)tir.dist;
		tir.dist = (tir.dist - (int)tir.dist) * 1000.0;
		tir.y = round(tir.dist);
		change_map(game, (int)tir.x, (int)tir.y, '0');
	}
}

void	teleportation(t_player *player, double x, double y)
{
	player->pos.x = x;
	player->pos.y = y;
}

void	change_map(t_game *game, int x, int y, char chr)
{
	game->map[y][x] = chr;
}

void	change_pv(t_player *player, float pv)
{
	player->pv = player->pv + pv;
	if (player->pv > 100)
		player->pv = 100;
	else if (player->pv <= 0.1)
		exit(0);
}
