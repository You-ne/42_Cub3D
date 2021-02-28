/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 03:41:39 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 03:47:54 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	param_enemy4(t_game *game, t_enemy *enemy, char chr)
{
	if (chr == ')')
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

void	param_enemy3(t_game *game, t_enemy *enemy, char chr)
{
	if (chr == '(')
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
}

void	param_enemy2(t_game *game, t_enemy *enemy, char chr)
{
	if (chr == 'k')
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
	param_enemy3(game, enemy, chr);
}

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
	param_enemy2(game, enemy, chr);
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
