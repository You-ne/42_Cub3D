/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/01 01:18:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_coor	ft_dirsteps(t_coor vecray)
{
	t_coor dir;

	if (vecray.x > 0)
		dir.x = 1;
	else if (vecray.x == 0)
		dir.x = -2;
	else
		dir.x = 0;
	if (vecray.y > 0)
		dir.y = 1;
	else
		dir.y = 0;
	return (dir);
}

int		is_str_charset(char *charset, char *str)
{
	int		i;
	int		j;

	i = 0;
	if (!str || !str[i] || !charset)
		return (0);
	while (str[i])
	{
		j = 0;
		while (charset[j] && (charset[j] != str[i]))
			j++;
		if (!charset[j])
			return (0);
		i++;
	}
	return (1);
}

int		in_str(char c, char *str)
{
	int		i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		count_animation_sprites(t_img *tex)
{
	t_img	*tmp;
	int		i;

	tmp = tex->next;
	i = 1;
	while (tmp->chr == tex->chr)
	{
		i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (i);
}

t_enemy	*find_enemy(t_game *game, int x, int y, char chr)
{
	t_enemy	*enemy;

	enemy = game->enemies;
	while (!(enemy->x == x && enemy->y == y &&
	(enemy->chr == chr || chr == find_death_chr(enemy->chr) ||
	enemy->chr == find_shooting_chr(chr))))
		enemy = enemy->next;
	return (enemy);
}
