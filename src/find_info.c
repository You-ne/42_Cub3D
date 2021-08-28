/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 02:30:05 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:12:10 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_info_5(char *info, t_game *game)
{
	int		found;

	found = 0;
	if (info[0] == 'S' && info[1] == ' ')
		save_sprite(info + 1, game, '2', 'S') ? found++ : found++;
	else if (info[0] == 'S' && info[1] != 'O' && info[1] != 'A')
		save_sprite(info + 2, game, info[1], 'S') ? found++ : found++;
	else if (info[0] == 'S' && info[1] == 'A')
		save_sprite(info + 4, game, info[3], 'A') ? found++ : found++;
	if (found == 0)
		ft_error("There's a key without info in .cub file!\n", game);
}

void	find_info_4(char *info, t_game *game)
{
	int		found;

	found = 0;
	if (info[0] == 'S' && info[1] == 'O')
	{
		if (game->found[3] == 1)
			ft_error("South texture appear twice!\n", game);
		save_texture(info + 2, game, 'S') ? found++ : found++;
		game->found[3] = 1;
	}
	if (info[0] == 'W' && info[1] == 'E')
	{
		if (game->found[4] == 1)
			ft_error("West texture appear twice!\n", game);
		save_texture(info + 2, game, 'W') ? found++ : found++;
		game->found[4] = 1;
	}
	if (found == 0)
		find_info_5(info, game);
}

void	find_info_3(char *info, t_game *game)
{
	int		found;

	found = 0;
	if (info[0] == 'E' && info[1] == 'A')
	{
		if (game->found[5] == 1)
			ft_error("Floor color appear twice!\n", game);
		save_texture(info + 2, game, 'E') ? found++ : found++;
		game->found[5] = 1;
	}
	if (info[0] == 'K' && info[1] == 'Y')
	{
		if (game->found[6] == 1)
			ft_error("Skybox path appears to times!\n", game);
		save_texture(info + 2, game, 'Y') ? found++ : found++;
		game->found[6] = 1;
	}
	if (found == 0)
		find_info_4(info, game);
}

void	find_info_2(char *info, t_game *game)
{
	int		found;

	found = 0;
	if (info[0] == 'C' && game->ce == 0)
	{
		if (game->found[1] == 1)
			ft_error("Ceiling color appear twice!\n", game);
		get_color(info, game, 'C') ? found++ : found++;
		game->found[1] = 1;
	}
	if (info[0] == 'N' && info[1] == 'O')
	{
		if (game->found[2] == 1)
			ft_error("North texture appear twice!\n", game);
		save_texture(info + 2, game, 'N') ? found++ : found++;
		game->found[2] = 1;
	}
	if (found == 0)
		find_info_3(info, game);
}

void	find_info(char *info, t_game *game)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (info[i] != 0 && !(info[i] > 65 && info[i] < 91))
		i++;
	if (info[i] == 'R')
	{
		if (game->found[7] == 2)
			ft_error("Resolution appears twice!\n", game);
		if (game->found[7] == 1)
			game->found[7] += 1;
		found++;
	}
	if (info[i] == 'F' && game->fl == 0)
	{
		if (game->found[0] == 1)
			ft_error("Floor color appear twice!\n", game);
		get_color(info + i, game, 'F') ? found++ : found++;
		game->found[0] = 1;
	}
	if (found == 0)
		find_info_2(info + i, game);
}
