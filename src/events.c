/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/22 05:30:52 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	change_enemy_pv(t_game *game, t_enemy *enemy, int pv)
{
	if (enemy->pv > 1)
	{
		enemy->pv = enemy->pv + pv;
		if (enemy->pv < 1)
		{
			enemy->tdeath = clock();
			change_map(game, enemy->x, enemy->y, find_death_chr(enemy->chr));
				if (enemy->chr == 'H')
					game->victory = clock();
		}
	}
}

void	weapon_fire(t_game *game, t_coor *tir)
{
	t_coor	*tir2;
	t_enemy	*enemy;

	tir2 = tir;
	if (tir->next != NULL)
	{
		while (tir->next->next != NULL)
				tir = tir->next;
		if ((int)game->res[1] / 2 > (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist)) / 2))) ||
		game->res[1] / 2 < (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist))) / 2)) -
		tir->next->y || is_alive_or_dead((char)((int)tir->next->dist) == -1))
		{
			tir->next = NULL;
			weapon_fire(game, tir2);
			return ;
		}
		if (is_alive_or_dead((char)((int)tir->next->dist)) != 1)
			return ;
		enemy = find_enemy(game, (int)((tir->next->dist - (int)tir->next->dist)
		* 1000.0), (int)roundf(((tir->next->dist * 1000) - (int)
		(tir->next->dist * 1000)) * 1000.0), (char)((int)tir->next->dist));
		change_enemy_pv(game, enemy, game->player.damage);
	}
}


void	teleportation(t_player *player, float x, float y)
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
}

