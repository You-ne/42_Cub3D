/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:15:09 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/20 22:29:04 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

void	get_res(char *info, t_game *game)  // norme
{
	int		i;
	int		j;

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

int		save_texture(char *info, t_game *game, char param) //norme
{
	int		i;

	i = 0;
	while (info[i] == ' ')
		i++;
	if (info[i] == '.')
	{
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
			ft_error("An RGB in is < 0 or > 255 please check the map \n", game);
		game->Fl = (game->F[0] * 256 * 256) + (game->F[1] * 256) + game->F[2];
	}
	if (param == 'C')
	{
		if (game->C[0] < 0 || game->C[0] > 255 || game->C[1] < 0 || game->C[1] > 255 || game->C[2] < 0 ||game->C[2] > 255)
			ft_error("An RGB in is < 0 or > 255 please check the map \n", game);
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
			{
				game->F[j] = ft_atoi(info + i);
			}
			if (param == 'C')
			{
				game->C[j] = ft_atoi(info + i);//check colors
			}
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


void	find_info_2(char *info, t_game *game)  //norme
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (info[i] != '\0')
	{
		if (info[i] == 'S' && info[i + 1] != 'O' && info[i + 1] != 'A' && found == 0)
			save_sprite(info + i + 2, game, info[i + 1], 'S') ? found++ : found++;
		if (info[i] == 'S' && info[i + 1] == 'A'  && found == 0)
			save_sprite(info + i + 5, game, info[i + 4], 'A') ? found++ : found++;
		if (info[i] == 'K' && info[i + 1] == 'Y')
			save_texture(info + i + 2, game, 'Y') ? found++ : found++;
		i++;
	}
}

void	find_info(char *info, t_game *game) // norme
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	printf("%s\n", info);
	while (info[i] != '\0')
	{
		if (info[i] == 'F' && found == 0 && game->Fl == 0)
			get_color(info + i, game, 'F') ? found++ : found++;
		if (info[i] == 'C' && found == 0 && game->Ce == 0)
			get_color(info + i, game, 'C') ? found++ : found++;
		if (info[i] == 'N' && info[i + 1] == 'O' && found == 0)
			save_texture(info + i + 2, game, 'N') ? found++ : found++;
		if (info[i] == 'S' && info[i + 1] == 'O' && found == 0)
			save_texture(info + i + 2, game, 'S') ? found++ : found++;
		if (info[i] == 'W' && info[i+1] == 'E' && found == 0)
			save_texture(info + i + 2, game, 'W') ? found++ : found++;
		if (info[i] == 'E' && info[i+1] == 'A' && found == 0)
			save_texture(info + i + 2, game, 'E') ? found++ : found++;
		i++;
	}
	if (found == 0)
		find_info_2(info, game);
}
