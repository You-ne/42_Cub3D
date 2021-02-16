/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/16 00:01:51 by antoine          ###   ########.fr       */
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
		}
	}
}

void	weapon_fire(t_game *game, t_coor *tir)
{
	int		x;
	int		y;
	int		mid;
	t_coor	*tir2;
	t_enemy	*enemy;

	mid = game->tilt + (int)(game->res[1] / 2);
	tir2 = tir;
//	system("aplay ./sprites/gun_shot.wav $");
//	tir = ft_raycannon(game->player.pos, game->player.vect, 0.0, game);
	if (tir->next != NULL)
	{
		while (tir->next->next != NULL)
				tir = tir->next;
		if ((int)game->res[1] / 2 > mid + ((tir->next->y * 
		(1 / sp_size((char)((int)tir->next->dist)) / 2))) ||
		game->res[1] / 2 < mid + ((tir->next->y * 
		(1 / sp_size((char)((int)tir->next->dist))) / 2)) - tir->next->y ||
		(char)((int)tir->next->dist) == ':' || 
		(char)((int)tir->next->dist) == '$' || (char)((int)tir->next->dist) == '=')
		{
			tir->next = NULL;
			weapon_fire(game, tir2);
			return ;
		}
		if ((char)((int)tir->next->dist) != '5' && 
		(char)((int)tir->next->dist) != '@' && (char)((int)tir->next->dist) != '#'
		&& (char)((int)tir->next->dist) != '!' && 
		(char)((int)tir->next->dist) != 'M' && 
		(char)((int)tir->next->dist) != 'H')
			return ;
		x = (int)((tir->next->dist - (int)tir->next->dist) * 1000.0);
		y = (int)round(((tir->next->dist * 1000) -
		(int)(tir->next->dist * 1000)) * 1000.0);
		enemy = find_enemy(game, x, y, (char)((int)tir->next->dist));
		change_enemy_pv(game, enemy, DAMAGE);
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

