/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/28 03:51:05 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		is_alive_or_dead(char chr)
{
	if (chr == 'e' || chr == 'V' || chr == 'c' || chr == 'M' || chr == 'H'
	|| chr == '(' || chr == 'A' || chr == 'X' || chr == ';' || chr == 'l'
	|| chr == 'x' || chr == 'I' || chr == '#' || chr == 's' || chr == '@'
	|| chr == 'U' | chr == '<' || chr == '{' || chr == ')' || chr == 'k'
	|| chr == 'y' || chr == 'r')
		return (1);
	if (chr == ':' || chr == '$' || chr == '=' || chr == 't' || chr == ','
	|| chr == 'a' || chr == '|' || chr == '}' || chr == 'z' | chr == '>')
		return (-1);
	return (0);
}

int		sp_collision(int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '*' ||
	map[y][x] == '6' || map[y][x] == '7' || map[y][x] == '8' ||
	map[y][x] == '9' || map[y][x] == '/' || map[y][x] == 'P' ||
	map[y][x] == 'e' || map[y][x] == 'V' || map[y][x] == 'C' ||
	map[y][x] == 'M' || map[y][x] == 'H' || map[y][x] == 'X' ||
	map[y][x] == 'A' || map[y][x] == 'l' || map[y][x] == 'I' ||
	map[y][x] == 's' || map[y][x] == 'U' || map[y][x] == '<' ||
	map[y][x] == '{' || map[y][x] == ')' || map[y][x] == 'k' ||
	map[y][x] == 'y' || map[y][x] == 'r')
	{
		system("aplay -N -q ./sprites/collision.wav &");
		return (1);
	}
	else
		return (0);
}

void	key_found(t_game *game)
{
	change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	if (game->secret.dist == 1)
		change_map(game, (int)game->secret.x, (int)game->secret.y, '0');
}

void	sp_events(t_game *game)
{
	char	chr;

	chr = game->map[(int)game->player.pos.y][(int)game->player.pos.x];
	if (chr == '2')
		teleportation(&game->player, 61.5, 12.5);
	if (chr == '3')
	{
		game->player.ammo += 15;
		if (game->player.ammo > 30)
			game->player.ammo = 30;
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
	if (chr == '4')
	{
		change_pv(&game->player, 15);
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
	if (chr == '5')
		key_found(game);
	if (chr == '~')
	{
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
		game->player.num_weapon = 2;
		game->player.damage = -100;
	}
}
