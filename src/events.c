/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/28 10:38:15 by antoine          ###   ########.fr       */
//Colors
#/*                                                                            */
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
			if (find_death_chr(enemy->chr) == 'H')
				system("aplay -N -q ./cont/sounds/Nein.wav &");
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
		printf("a_or_d=%i; chr=%c\n", is_alive_or_dead((char)((int)tir->next->dist)), (char)((int)tir->next->dist));
		if (is_alive_or_dead((char)((int)tir->next->dist) < 0) ||
		((int)game->res[1] / 2 > (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist)) / 2))) ||
		game->res[1] / 2 < (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist))) / 2)) -
		tir->next->y))
		{
			write(1, "A", 1);
			free_ray(tir->next);
			tir->next = NULL;
			weapon_fire(game, tir2);
			return ;
		}
		if (is_alive_or_dead((char)((int)tir->next->dist)) != 1)
			return ;
		enemy = find_enemy(game, tir->next->coor_sp / 1000,
		tir->next->coor_sp % 1000, (char)((int)tir->next->dist));
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
	if (player->pv <= 0)
		system("aplay -N -q ./cont/sounds/Cri_wilhelm.wav &");
	return ;
}

