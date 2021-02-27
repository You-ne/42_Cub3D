/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:15:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 00:32:45 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

void	get_res(char *info, t_game *game)  // norme
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
			while(info[i] > 47 && info[i] < 58)
				i++;
		}
		if (info[i] != 0 && info[i + 1] != 0)
			i++;
	}
	check_res(game);
}

int		save_texture(char *info, t_game *game, char param) //norme
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
			extract_texture(game, info + i, "NO", '\0');
		if (param == 'S')
			extract_texture(game, info + i, "SO", '\0');
		if (param == 'W')
			extract_texture(game, info + i, "WE", '\0');
		if (param == 'E')
			extract_texture(game, info + i, "EA", '\0');
		if (param == 'Y')
			extract_texture(game, info + i, "KY", '\0');
	}
	else
		ft_error("Please enter a valid path for textures !!\n", game);
	return (0);
}

int		save_sprite(char *info, t_game *game, char chr, char mode) // norme
{
	int		i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.' && info[i + 1 ] == '/' )
	{
		checkpath(info + i, game);
		if (mode == 'S')
			extract_texture(game, info + i, "SP", chr);
		if (mode == 'A')
			extract_anim(game, info + i, chr);
	}
	else
		ft_error("Please enter a valid path for sprites textures !!\n", game);
	return (0);
}

void		check_colors(t_game *game, char param)
{
	if (param == 'F')
	{		
		if (game->F[0] < 0 || game->F[0] > 255 || game->F[1] < 0 || game->F[1] > 255 || game->F[2] < 0 ||game->F[2] > 255)
			ft_error("An RGB int is < 0 or > 255 please check the map\n", game);
		game->Fl = (game->F[0] * 256 * 256) + (game->F[1] * 256) + game->F[2];
	}
	if (param == 'C')
	{
		if (game->C[0] < 0 || game->C[0] > 255 || game->C[1] < 0 || game->C[1] > 255 || game->C[2] < 0 ||game->C[2] > 255)
			ft_error("An RGB int is < 0 or > 255 please check the map\n", game);
		game->Ce = (game->C[0] * 256 * 256) + (game->C[1] * 256) + game->C[2];
	}
}

int		get_color(char *info, t_game *game, char param) // a modif
{
	int		i;
	int		j;

	j = 0;
	i  = 0;
	while(info[i] != '\0' && j < 3)
	{
		if(info[i] > 47 && info[i] < 58)
		{
			if (param == 'F')
				game->F[j] = ft_atoi(info + i);
			if (param == 'C')
				game->C[j] = ft_atoi(info + i);//check colors
			j++;
			while(info[i] > 47 && info[i] < 58 && info [i] != '\0')
				i++;
			if (info[i] == '\0')
				break;
		}
		i++;
	}
	if (j != 3)
		ft_error("Wrong number of ints for RGB color !\n", game);
	check_colors(game, param);
	return (0);
}

void	find_info_5(char *info, t_game *game)
{
	int		found;

	found = 0;
	if (info[0] == 'S' && info[1] != 'O' && info[1] != 'A')
		save_sprite(info + 2, game, info[1], 'S') ? found++ : found++;
	if (info[0] == 'S' && info[1] == 'A')
		save_sprite(info + 5, game, info[4], 'A') ? found++ : found++;
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

void	find_info_3(char *info, t_game *game)  //norme
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

void	find_info_2(char *info, t_game *game)  //norme
{
	int		found;

	found = 0;
	if (info[0] == 'C' && game->Ce == 0)
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

void	find_info(char *info, t_game *game) // norme
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
		if (game->found[7] == 1);
			game->found[7] +=1;
		found++;
	}
	if (info[i] == 'F' && game->Fl == 0)
	{
		if (game->found[0] == 1)
			ft_error("Floor color appear twice!\n", game);
		get_color(info + i, game, 'F') ? found++ : found++;
		game->found[0] = 1;
	}
	if (found == 0)
		find_info_2(info + i, game);
}
