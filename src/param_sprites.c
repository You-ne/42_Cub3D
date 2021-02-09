/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/09 02:09:43 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		sp_collision(int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '3' || map[y][x] == '5')
		return (1);
	else
		return (0);
}

double	sp_size(char chr)
{
	double size;

	size = 1.0;
	if (chr == '2')
		size = 0.3;
	if (chr == '3')
		size = 1.1;
	if (chr == '5')
		size = 0.7;
	return (size);
}

void	sp_events(t_game *game)
{
	char chr;
	static clock_t t1;
	static int atk;
	clock_t t2;
	char **map;
	float	centisec;

	map = game->map;
	chr = map[(int)game->player.pos.y][(int)game->player.pos.x];
	if (chr == '2')
		teleportation(&game->player, 61.5, 12.5);
	if (map[(int)game->player.pos.y + 1][(int)game->player.pos.x] == '5' ||
		map[(int)game->player.pos.y - 1][(int)game->player.pos.x] == '5' ||
		map[(int)game->player.pos.y][(int)game->player.pos.x + 1] == '5' ||
		map[(int)game->player.pos.y][(int)game->player.pos.x - 1] == '5' ||
		map[(int)game->player.pos.y - 1][(int)game->player.pos.x - 1] == '5' ||
		map[(int)game->player.pos.y + 1][(int)game->player.pos.x + 1] == '5' ||
		map[(int)game->player.pos.y - 1][(int)game->player.pos.x + 1] == '5' ||
		map[(int)game->player.pos.y + 1][(int)game->player.pos.x - 1] == '5')
	{
		if (!t1)
			t1 = clock();
		t2 = clock();
		centisec = ((double)(t2 - t1) / CLOCKS_PER_SEC) * 100;
		if (centisec >= 50)
		{
			change_pv(&game->player, -20);
			t1 = 0;
		}
	}
	else
		t1 = 0;
	if (chr == '4')
	{
		change_pv(&game->player, 15);
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
}