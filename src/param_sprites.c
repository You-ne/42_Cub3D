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

int		sp_collision(int x, int y, t_game *g)
{
	if (g->map[y][x] == '1' || g->map[y][x] == '*' || g->map[y][x] == '2' ||
	g->map[y][x] == '6' || g->map[y][x] == '7' || g->map[y][x] == '8' ||
	g->map[y][x] == '/' || g->map[y][x] == 'P' || g->map[y][x] == '#' ||
	g->map[y][x] == 'e' || g->map[y][x] == 'V' || g->map[y][x] == 'c' ||
	g->map[y][x] == 'M' || g->map[y][x] == 'H' || g->map[y][x] == 'X' ||
	g->map[y][x] == 'A' || g->map[y][x] == 'l' || g->map[y][x] == 'I' ||
	g->map[y][x] == 's' || g->map[y][x] == 'U' || g->map[y][x] == '<' ||
	g->map[y][x] == '{' || g->map[y][x] == ')' || g->map[y][x] == 'k' ||
	g->map[y][x] == 'y' || g->map[y][x] == 'r' || g->map[y][x] == 'i' ||
	g->map[y][x] == 'T' || g->map[y][x] == '&' || g->map[y][x] == '(' ||
	g->map[y][x] == ';' || g->map[y][x] == '@')
	{
		if (system("aplay -N -q ./cont/sounds/collision.wav &") == -1)
			ft_error("Erreur: aplay a échoué !\n", g);
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
