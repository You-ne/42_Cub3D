/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 20:44:44 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/27 07:41:13 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	param_enemy(t_game *game, t_enemy *enemy, char chr)
{

	if (chr == 'r')
	{
		enemy->pv = 100;
		enemy->damage = -5;
		enemy->time_anim = 50;
	}
	else if (chr == 'f')
	{
		enemy->pv = 10000;
		enemy->damage = 0;
		enemy->time_anim = 50;
	}
	else if (chr == 'y')
	{
		enemy->pv = 100;
		enemy->damage = -15;
		enemy->time_anim = 150;
	}
	else if (chr == 'k')
	{
		enemy->pv = 150;
		enemy->damage = -10;
		enemy->time_anim = 150;
	}
	else if (chr == 'I')
	{
		enemy->pv = 150;
		enemy->damage = -20;
		enemy->time_anim = 150;
	}
	else if (chr == ';')
	{
		enemy->pv = 100;
		enemy->damage = -25;
		enemy->time_anim = 150;
	}
	else if (chr == '(')
	{
		enemy->pv = 250;
		enemy->damage = -15;
		enemy->time_anim = 200;
	}
	else if (chr == '<')
	{
		enemy->pv = 300;
		enemy->damage = -1;
		enemy->time_anim = 150;
	}
	else if (chr == '@')
	{
		enemy->pv = 300;
		enemy->damage = -15;
		enemy->time_anim = 200;
	}
	else if (chr == ')')
	{
		enemy->pv = 250;
		enemy->damage = -30;
		enemy->time_anim = 80;
	}
	else if (chr == '{')
	{
		enemy->pv = 250;
		enemy->damage = -15;
		enemy->time_anim = 120;
	}

}

t_img	*find_animation(t_game *game, int info, t_img *tex, char chr)
{
	int x1;
    int y1;

	x1 = info / 1000;
	y1 = info % 1000;
	if (chr == 'e' || chr == 'V' || chr == 'C' || chr == 'M' || chr == 'X' ||
        chr == 'A' || chr == 'l' || chr == 'I' || chr == 's' || chr == 'U')
		tex = enemy_fire_animation(game, tex, find_enemy(game, x1, y1, chr));
	else if (chr == '-' || chr == '+' || chr == '%' || chr == '?' || chr == 'm' 
		|| chr == 'h' || chr == 'x' || chr == 'L' || chr == 'o' || chr == 'u')
		tex = death_animation(game, tex, find_enemy(game, x1, y1, chr));
	else if (chr == 'f' || chr == '(' || chr == ';' || chr == '#' || chr == '@'
			||chr == '<' || chr == '{' || chr == ')' || chr == 'k' || chr == 'y'
			|| chr == 'r')
	{
		tex = aim_animation(game, tex, find_enemy(game, x1, y1, chr));
	}
	return (tex);
}

int	is_alive_or_dead(char chr)
{
	if (chr == 'e' || chr == 'V' || chr == 'c' || chr == 'M' || chr == 'H'
	|| chr == '(' || chr == 'A' || chr == 'X' || chr == ';' || chr == 'l'
	 || chr == 'x' || chr == 'I' || chr == '#' || chr == 's' || chr == '@' 
	 || chr == 'U' | chr == '<' || chr == '{' || chr == ')' || chr == 'k'
	 || chr == 'y' || chr == 'r')
		return (1);
	if (chr == ':' || chr == '$' || chr  == '=' || chr == 't' || chr == ','
	|| chr == 'a' || chr == '|' || chr == '}' || chr == 'z' | chr == '>')
		return (-1);
	return (0);
}

char	find_shooting_chr(char chr)
{
	if (chr == 'f')
		return ('0');
	if (chr == '(')
		return ('A');
	if (chr == ';')
		return ('l');
	if (chr == '#')
		return ('s');
	if (chr == '@')
		return ('U');
	if (chr == '<')
		return ('X');
	if (chr == '{')
		return ('H');
	if (chr == ')')
		return ('M');
	if (chr == 'k')
		return ('C');
	if (chr == 'y')
		return ('V');
	if (chr == 'r')
		return ('e');
	return ('\0');
}

char	find_death_chr(char chr)
{
	if (chr == 'e')
		return ('+');
	if (chr == '+')
		return ('=');
	if (chr == 'V')
		return ('%');
	if (chr == '%')
		return ('$');
	if (chr == 'c')
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
	if (chr == 'A')
		return ('-');
	if (chr == '-')
		return (',');
	if (chr == 'X')
		return ('x');
	if (chr == 'x')
		return ('a');
	if (chr == 'l')
		return ('L');
	if (chr == 'L')
		return ('|');
	if (chr == 'I')
		return ('o');
	if (chr == 'o')
		return ('}');
	if (chr == 's')
		return ('_');
	if (chr == '_')
		return ('z');
	if (chr == 'U')
		return ('u');
	if (chr == 'u')
		return ('>');
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

float	sp_size(char chr)
{
	float size;

	size = 1.0;
	if (chr == '2')
		size = 0.3;
	if (chr == 'e' || chr == '+' || chr == '=' || chr == 'V' || chr == '%' ||
	chr == '$' || chr == 'C' || chr == '?' || chr == ':' || chr == ';' ||
	chr == 'l' || chr == 'L' || chr == '|' || chr == 'I' || chr == 'o' || 
	chr == '}' || chr == '#' || chr == 's' || chr == '_' || chr == 'z' || 
	chr == 'f' || chr == 'k' || chr == 'y' || chr == 'r')
		size = 0.6;
	if (chr == '3')
		size = 0.4;
	if (chr == '4')
		size = 0.5;
	if (chr == 'M' || chr == 'm' || chr == 'H' || chr == 'h' || chr == 'X' ||
		chr == 'x' || chr == 'a' || chr == 'A' || chr == '-' || chr == ',' || 
		chr == '@' || chr == 'U' || chr == 'u' || chr == '>' || chr == '<' ||
		chr == '{' || chr == ')')
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
