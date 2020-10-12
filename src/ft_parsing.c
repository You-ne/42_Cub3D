/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:15:09 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/12 13:31:36 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

void	get_res(char *info, t_game *game)
{	
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(info[i] != '\0')
	{ 
		if(info[i] > 47 && info[i] < 58)
		{
			if (j == 0)
			{
				game->res[0] = ft_atoi(info + i);
				j++;
			}
			else
			{
				game->res[1] = ft_atoi(info + i);
				return;
			}
			while(info[i] > 47 && info[i] < 58)
				i++;
		}
		i++;
	}

}

void	save_texture_path(char *info, t_game *game, char param)
{
	int	i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.' && info[i + 1 ] == '/')
	{
		if (param == 'N')
		game->NO.path = extract_path(game->NO.path, info + i);
		if (param == 'S')
		game->SO.path = extract_path(game->SO.path, info + i);
		if (param == 'W')
		game->WE.path = extract_path(game->WE.path, info + i);
		if (param == 'E')
		game->EA.path = extract_path(game->EA.path, info + i);
	}
}

void	save_sprite_path(char *info, t_game *game)
{
	int	i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.' && info[i + 1 ] == '/')
		game->SP.path = extract_path(game->SP.path, info + i);
}

void	get_color(char *info, t_game *game, char param)
{
	int	i;
	int	j;

	j = 0;
	i  = 0;
	while(info[i] != '\0' && j < 3)
	{
		if(info[i] > 47 && info[i] < 58)
		{
			if (param == 'F')
				game->F[j] = ft_atoi(info + i);
			if (param == 'C')
				game->C[j] = ft_atoi(info + i);
			j++;
			while(info[i] > 47 && info[i] < 58 && info [i] != '\0')
				i++;
			if (info[i] == '\0')
				break;
		}	
		i++;
	}
	game->Fl = (game->F[0] * 256 * 256) + (game->F[1] * 256) + game->F[2];
	game->Ce = (game->C[0] * 256 * 256) + (game->C[1] * 256) + game->C[2];
}

void	find_info(char *info, t_game *game)
{
	int	i;

	i = 0;
	while (info[i] != '\0')
	{
		if (info[i] == 'R')
			get_res(info + i, game);
		if (info[i] == 'N')
			save_texture_path(info + i, game, 'N');
		if (info[i] == 'S' && info[i + 1] == 'O')
			save_texture_path(info + i, game, 'S');
		if (info[i] == 'W')
			save_texture_path(info + i, game, 'W');
		if (info[i] == 'E')
			save_texture_path(info + i, game, 'E');
		if (info[i] == 'S' && info[i + 1] == 'P')
			save_sprite_path(info + i, game);
		if (info[i] == 'F')
			get_color(info + i, game, 'F');
		if (info[i] == 'C')
			get_color(info + i, game, 'C');
		i++;
	}
}
