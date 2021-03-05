/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/03/04 03:51:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_alive_or_dead(char chr)
{
	if (chr == 'e' || chr == 'V' || chr == 'c' || chr == 'M' || chr == 'H'
	|| chr == '(' || chr == 'A' || chr == 'X' || chr == ';' || chr == 'l'
	|| chr == 'x' || chr == 'I' || chr == '#' || chr == 's' || chr == '@'
	|| chr == 'U' || chr == '<' || chr == '{' || chr == ')' || chr == 'k'
	|| chr == 'y' || chr == 'r' || chr == 'i')
		return (1);
	else if (chr == ':' || chr == '$' || chr == '=' || chr == 't' || chr == ','
	|| chr == 'a' || chr == '|' || chr == '}' || chr == 'z' || chr == '>' ||
	chr == '_' || chr == 'p' || chr == '+' || chr == '%' || chr == '?' ||
	chr == 'm' || chr == 'h' || chr == 'x' || chr == '-' || chr == 'L' ||
	chr == 'o' || chr == 'u')
		return (-1);
	return (0);
}

int		sp_collision(int x, int y, char ***map, t_game *game)
{
	if (*map[y][x] == '1' || *map[y][x] == '*' || *map[y][x] == '2' ||
	*map[y][x] == '6' || *map[y][x] == '7' || *map[y][x] == '8' ||
	*map[y][x] == '/' || *map[y][x] == 'P' || *map[y][x] == '#' ||
	*map[y][x] == 'e' || *map[y][x] == 'V' || *map[y][x] == 'c' ||
	*map[y][x] == 'M' || *map[y][x] == 'H' || *map[y][x] == 'X' ||
	*map[y][x] == 'A' || *map[y][x] == 'l' || *map[y][x] == 'I' ||
	*map[y][x] == 's' || *map[y][x] == 'U' || *map[y][x] == '<' ||
	*map[y][x] == '{' || *map[y][x] == ')' || *map[y][x] == 'k' ||
	*map[y][x] == 'y' || *map[y][x] == 'r' || *map[y][x] == 'i' ||
	*map[y][x] == 'T' || *map[y][x] == '&' || *map[y][x] == '(' ||
	*map[y][x] == ';' || *map[y][x] == '@')
	{
		if (system("aplay -N -q ./cont/sounds/collision.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", game);
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

void	sp_events2(t_game *game, char chr)
{
	if (chr == '4')
	{
		if (system("aplay -N -q ./cont/sounds/rot.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", game);
		change_pv(game, 15);
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
	else if (chr == '5')
	{
		if (system("aplay -N -q ./cont/sounds/door.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", game);
		key_found(game);
	}
	else if (chr == '~')
	{
		if (system("aplay -N -q ./cont/sounds/TakeWeapon.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", game);
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
		game->player.num_weapon = 2;
		game->player.damage = -80;
	}
}

void	sp_events(t_game *game)
{
	char	chr;

	chr = game->map[(int)game->player.pos.y][(int)game->player.pos.x];
	if (chr == '9')
		teleportation(game, 46.5, 3.5);
	else if (chr == 'w')
		teleportation(game, 1.5, 22.5);
	else if (chr == '3')
	{
		if (system("aplay -N -q ./cont/sounds/recharger.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", game);
		game->player.ammo += 10;
		if (game->player.ammo > AMMO_MAX)
			game->player.ammo = AMMO_MAX;
		change_map(game, (int)game->player.pos.x, (int)game->player.pos.y, '0');
	}
	else
		sp_events2(game, chr);
}
