/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/22 05:33:11 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_img	find_animation(t_game *game, float info, t_img tex)
{
	int x1;
	int y1;
	char chr;

	chr = (char)((int)info);
	x1 = (int)((info - (int)info) * 1000.0);
	y1 = (int)roundf(((info * 1000) - (int)(info * 1000)) * 1000.0);
	if (chr == '@' || chr == '#' || chr == '!'|| chr == 'H' || chr == 'M')
		tex = enemy_fire_animation(game, &tex, find_enemy(game, x1, y1, chr));
	else if (chr == '+' || chr == '%' || chr == '?' || chr == 'm' || chr == 'h')
		tex = death_animation(game, &tex, find_enemy(game, x1, y1, chr));
	else if (chr == '\0')
		tex = aim_animation(game, &tex, find_enemy(game, x1, y1, chr));
	return (tex);
}

int	is_alive_or_dead(char chr)
{
	if (chr == '@' || chr == '#' || chr == '!' || chr == 'M' || chr == 'H')
		return (1);
	if (chr == ':' || chr == '$' || chr  == '=')
		return (-1);
	return (0);
}

char	find_shooting_chr(char chr)
{
	return ('\0');
}

char	find_death_chr(char chr)
{
	if (chr == '@')
		return ('+');
	if (chr == '+')
		return ('=');
	if (chr == '#')
		return ('%');
	if (chr == '%')
		return ('$');
	if (chr == '!')
		return ('?');
	if (chr == '?')
		return (':');
	if (chr == 'M')
		return ('m');
	if (chr == 'm')
		return ('H');
	if (chr == 'H')
		return ('h');
	if (chr == 'h')
		return ('t');


}

int		sp_collision(int x, int y, char **map)
{
	if (map[y][x] == '1' || map[y][x] == '3' || map[y][x] == '*' ||
	map[y][x] == '@' || map[y][x] == 'P' || map[y][x] == '#' ||
	map[y][x] == '!' || map[y][x] == 'M' || map[y][x] == 'm' ||
	map[y][x] == 'H')
		return (1);
	else
		return (0);
}

float	sp_size(char chr)
{
	float size;

	size = 1.0;
	if (chr == '2')
		size = 0.3;
	if (chr == '@' || chr == '#' || chr == '=' || chr == '+' || chr == '%' ||
	chr == '$' || chr == '!' || chr == '?' || chr == ':')
		size = 0.6;
	if (chr == '3')
		size = 1.1;
	if (chr == '4')
		size = 0.5;
	if (chr == 'M' || chr == 'm' || chr == 'H' || chr == 'h')
		size = 0.7;
	if (chr == 't')
		size = 0.2;
	if (chr == '5')
		size = 0.1;
	return (size);
}

void	key_found(t_game *game)
{
	change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	if (game->secret.dist == 1)
		change_map(game, (int)game->secret.x, (int)game->secret.y, '0');
}

void	sp_events(t_game *game)
{
	char chr;
	char **map;
	float	centisec;

	map = game->map;
	chr = map[(int)game->player.pos.y][(int)game->player.pos.x];
	if (chr == '2')
		teleportation(&game->player, 61.5, 12.5);
	if (chr == '5')
		key_found(game);
	if (chr == '=')
	{
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
		game->player.num_weapon = 2;
		game->player.damage = -100;
	}
	if (chr == '4')
	{
		change_pv(&game->player, 15);
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
}
