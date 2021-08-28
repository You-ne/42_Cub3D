/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 03:48:22 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/02 03:59:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*find_animation(t_game *game, int info, t_img *tex, char chr)
{
	int x1;
	int y1;

	x1 = info / 1000;
	y1 = info % 1000;
	if (chr == 'e' || chr == 'V' || chr == 'c' || chr == 'M' || chr == 'X' ||
	chr == 'A' || chr == 'l' || chr == 'I' || chr == 's' || chr == 'U' ||
	chr == 'H')
		tex = enemy_fire_animation(game, tex, find_enemy(game, x1, y1, chr));
	else if (chr == '-' || chr == '+' || chr == '%' || chr == '?' || chr == 'm'
	|| chr == 'h' || chr == 'x' || chr == 'L' || chr == 'o' || chr == 'u' ||
	chr == '_')
		tex = death_animation(game, tex, find_enemy(game, x1, y1, chr));
	else if (chr == 'f' || chr == '(' || chr == ';' || chr == '#' || chr == '@'
	|| chr == '<' || chr == '{' || chr == ')' || chr == 'k' ||
	chr == 'y' || chr == 'r' || chr == 'i')
		tex = aim_animation(game, tex, find_enemy(game, x1, y1, chr));
	return (tex);
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
		return ('c');
	if (chr == 'y')
		return ('V');
	if (chr == 'r')
		return ('e');
	if (chr == 'i')
		return ('I');
	return ('\0');
}

char	find_death_chr2(char chr)
{
	if (chr == 'A')
		return ('-');
	else if (chr == '-')
		return (',');
	else if (chr == 'X')
		return ('x');
	else if (chr == 'x')
		return ('a');
	else if (chr == 'l')
		return ('L');
	else if (chr == 'L')
		return ('|');
	else if (chr == 'I')
		return ('o');
	else if (chr == 'o')
		return ('}');
	else if (chr == 's')
		return ('_');
	else if (chr == '_')
		return ('z');
	else if (chr == 'U')
		return ('u');
	else if (chr == 'u')
		return ('>');
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
	else
		return (find_death_chr2(chr));
}
