/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/03/01 00:18:14 by antoine          ###   ########.fr       */
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
					game->end = clock();
		}
	}
}

void	weapon_fire(t_game *g, t_coor *t)
{
	t_coor	*tir2;
	t_enemy	*enemy;

	tir2 = t;
	if (t->next != NULL)
	{
		while (t->next->next != NULL)
				t = t->next;
		if (is_alive_or_dead((char)((int)t->next->dist)) < 0 || ((int)(g->res[1]
		/ 2) > (g->tilt + (int)(g->res[1] / 2)) + ((t->next->y * (1 / sp_size(
		(char)((int)t->next->dist)) / 2))) || g->res[1] / 2 < (g->tilt + (int)
		(g->res[1] / 2)) + ((t->next->y * (1 / sp_size((char)(
		(int)t->next->dist))) / 2)) - t->next->y))
		{
			free_ray(t->next);
			t->next = NULL;
			weapon_fire(g, tir2);
			return ;
		}
		if (is_alive_or_dead((char)((int)t->next->dist)) != 1)
			return ;
		enemy = find_enemy(g, t->next->coor_sp / 1000,
		t->next->coor_sp % 1000, (char)((int)t->next->dist));
		change_enemy_pv(g, enemy, g->player.damage);
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

void	change_pv(t_game *game, float pv)
{
	game->player.pv = game->player.pv + pv;
	if (game->player.pv > 100)
		game->player.pv = 100;
	if (game->player.pv <= 0)
	{
		game->end = clock();
		system("aplay -N -q ./cont/sounds/Cri_wilhelm.wav &");
	}
	return ;
}

