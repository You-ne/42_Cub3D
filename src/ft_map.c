/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:11:54 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_map(t_game *game, int line, int nlines, char *sp_set)
{
	char	**new;
	int		i;
	char	*new_set;

	i = 0;
	new_set = ft_strdup("1 ");
	new_set = ft_strmcat(new_set, sp_set);
	if (!(new = (char**)malloc(sizeof(char*) * (nlines + 1))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	while (game->map[line] != NULL)
	{
		if (!is_str_charset(new_set, game->map[line]) ||
		!in_str('1', game->map[line]))
			ft_error("Mauvais char dans la map !\n", game);
		new[i] = ft_strdup(game->map[line++]);
		if (!(new[i++]))
			ft_error("Erreur durant la copie de la map !\n", game);
	}
	new[i] = NULL;
	i = 0;
	while (game->map[i] != NULL)
		free(game->map[i++]);
	free(game->map);
	free(new_set);
	game->map = new;
}

void	add_enemy(int x, int y, char enemy_chr, t_game *game)
{
	t_enemy		*tmp;

	tmp = game->enemies;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->x != -1)
	{
		if (!(tmp->next = (t_enemy*)malloc(sizeof(t_enemy))))
			ft_error("Erreur: Malloc a échoué !\n", game);
		tmp = tmp->next;
	}
	tmp->x = x;
	tmp->y = y;
	tmp->fire = 0;
	tmp->tseen = -1;
	tmp->tdeath = -1;
	param_enemy(tmp, enemy_chr);
	tmp->chr = find_shooting_chr(enemy_chr);
	tmp->next = NULL;
}

void	get_enemies(t_game *game, char *foes_set)
{
	int		x;
	int		y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != 0)
		{
			if (in_str(game->map[y][x], foes_set))
			{
				add_enemy(x, y, game->map[y][x], game);
				if (game->map[y][x] == ')')
					add_enemy(x, y, '{', game);
			}
			x++;
		}
		y++;
	}
	free(foes_set);
}

char	*get_foes_char(t_img *enemies)
{
	t_img	*tmp;
	char	*set;
	char	*chr;

	tmp = enemies;
	set = ft_strdup("");
	while (tmp->next != NULL)
	{
		if (!(in_str(tmp->chr, set)))
		{
			chr = ft_ctostr(1, tmp->chr);
			set = ft_strmcat(set, chr);
			free(chr);
		}
		tmp = tmp->next;
	}
	return (set);
}

int		find_map(t_game *game, int line)
{
	int		end;
	char	*sp_set;
	char	*tmp_set;

	check_settings(game);
	tmp_set = ft_strdup("NEWS0");
	tmp_set = count_sprites(game, 0, tmp_set);
	sp_set = count_sprites(game, 1, tmp_set);
	end = line;
	while (game->map[end] != NULL)
		end++;
	get_map(game, line, end - line, sp_set);
	verify_map(game, sp_set);
	get_enemies(game, get_foes_char(game->sa));
	find_secret_door(game);
	free(sp_set);
	game->map_found = 1;
	return (1);
}
