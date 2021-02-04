/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/03 22:50:48 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	teleportation(t_player *player, double x, double y)
{
	player->pos.x = x;
	player->pos.y = y;
}

void	change_map(t_game *game, int x, int y, char chr)
{
	game->map[x][y] = chr;
}

void	change_pv(t_player *player, float pv)
{
	player->pv = player->pv + pv;
}
