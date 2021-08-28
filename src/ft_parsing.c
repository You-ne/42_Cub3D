/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:15:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:04:55 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_res(char *info, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (info[i] != '\0' &&
	((info[i] > 47 && info[i] < 58) || info[i] == ' '))
	{
		if (info[i] > 47 && info[i] < 58 && j < 2)
		{
			if (j == 0)
				game->res[j++] = ft_atoi(info + i);
			else
				game->res[j++] = ft_atoi(info + i);
			while (info[i] > 47 && info[i] < 58)
				i++;
		}
		if (info[i] != 0 && info[i + 1] != 0)
			i++;
	}
	check_res(game);
}

int		save_texture(char *info, t_game *game, char param)
{
	int		i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.')
	{
		checkpath(info + i, game);
		i = i + 2;
		if (param == 'N')
			extract_xpm(game, &game->no, info + i);
		if (param == 'S')
			extract_xpm(game, &game->so, info + i);
		if (param == 'W')
			extract_xpm(game, &game->we, info + i);
		if (param == 'E')
			extract_xpm(game, &game->ea, info + i);
		if (param == 'Y')
			extract_xpm(game, &game->sky, info + i);
	}
	else
		ft_error("Please enter a valid path for textures !!\n", game);
	return (0);
}

int		save_sprite(char *info, t_game *game, char chr, char mode)
{
	int		i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.' && info[i + 1] == '/')
	{
		checkpath(info + i, game);
		if (mode == 'S')
			extract_sprite(game, info + i, chr, game->sp);
		if (mode == 'A')
			extract_sprite(game, info + i, chr, game->sa);
	}
	else
		ft_error("Please enter a valid path for sprites textures !!\n", game);
	return (0);
}

void	check_colors(t_game *game, char param)
{
	if (param == 'F')
	{
		if (game->f[0] < 0 || game->f[0] > 255 || game->f[1] < 0 ||
		game->f[1] > 255 || game->f[2] < 0 || game->f[2] > 255)
			ft_error("An RGB int is > 0 or < 255 please check the map\n", game);
		game->fl = (game->f[0] * 256 * 256) + (game->f[1] * 256) + game->f[2];
	}
	if (param == 'C')
	{
		if (game->c[0] < 0 || game->c[0] > 255 || game->c[1] < 0 ||
		game->c[1] > 255 || game->c[2] < 0 || game->c[2] > 255)
			ft_error("An RGB int is > 0 or < 255 please check the map\n", game);
		game->ce = (game->c[0] * 256 * 256) + (game->c[1] * 256) + game->c[2];
	}
}

int		get_color(char *info, t_game *game, char param)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (info[i] != '\0' && j < 3)
	{
		if (info[i] > 47 && info[i] < 58)
		{
			if (param == 'F')
				game->f[j] = ft_atoi(info + i);
			if (param == 'C')
				game->c[j] = ft_atoi(info + i);
			j++;
			while (info[i] > 47 && info[i] < 58 && info[i] != '\0')
				i++;
			if (info[i] == '\0')
				break ;
		}
		i++;
	}
	if (j != 3)
		ft_error("Wrong number of ints for RGB color !\n", game);
	check_colors(game, param);
	return (0);
}
