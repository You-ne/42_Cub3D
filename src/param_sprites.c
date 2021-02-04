/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/03 23:11:48 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		sp_collision(int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '3')
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

	chr = game->map[(int)game->player.pos.y][(int)game->player.pos.x];
	if (chr == '2')
		teleportation(&game->player, 61.5, 12.5);
	if (chr == '5')
	{
		change_pv(&game->player, -0.5);
		printf("%.2f PV\n\n", game->player.pv);
	}
	if (chr == '4')
	{
		change_pv(&game->player, 0.7);
		printf("%.2f PV\n\n", game->player.pv);
	}
}
