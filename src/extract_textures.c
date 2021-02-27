/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 04:23:36 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/27 04:43:14 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	so_sky_textures(t_game *game, char param, char *str)
{
	if (param == 'S')
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SO.width, &game->SO.height);
		if (!(game->SO.img_p))
			ft_error("Troubles extracting SO texture !!\n", game);
		game->SO.img = mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
	}
	if (param == 'K')
	{
		game->SKY.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SKY.width, &game->SKY.height);
		if (!(game->SKY.img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		game->SKY.img = mlx_get_data_addr(game->SKY.img_p, &game->SKY.bpp, &game->SKY.s_line, &game->SKY.endian);
	}
}

void	no_we_ea_textures(t_game *game, char param, char *str)
{
	if (param == 'N')
	{
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->NO.width, &game->NO.height);
		if (!(game->NO.img_p))
			ft_error("Troubles extracting NO texture !!\n", game);
		game->NO.img = mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
	}
	if (param == 'W')
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->WE.width, &game->WE.height);
		if (!(game->WE.img_p))
			ft_error("Troubles extracting WE texture !!\n", game);
		game->WE.img = mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
	}
	if (param == 'E')
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->EA.width, &game->EA.height);
		if (!(game->EA.img_p))
			ft_error("Troubles extracting EA texture !!\n", game);
		game->EA.img = mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
	}
}

void	extract_sprite_2(t_game *game, char *str, char chr)
{
	t_img *tex;
	t_img *tmp;

	tmp = game->SP;
	tex = (struct s_img*)malloc(sizeof(struct s_img));
	tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &tex->width, &tex->height);
	if (!(game->SP->img_p))
		ft_error("Troubles extracting sprites textures !!\n", game);
	tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
	tex->chr = chr;
	tex->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = tex;
}

void	extract_sprite(t_game *game, char *str, char chr)
{
	if (chr == '2')
	{
		game->SP->img_p = mlx_xpm_file_to_image(game->win.mlxp, str,
		&game->SP->width, &game->SP->height);
		if (!(game->SP->img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		game->SP->img = mlx_get_data_addr(game->SP->img_p, &game->SP->bpp,
		&game->SP->s_line, &game->SP->endian);
		game->SP->chr = '2';
		game->SP->next = NULL;
	}
	else
		extract_sprite_2(game, str, chr);
}

void	extract_texture(t_game *game, char *str, char *img, char chr)
{
	if (img[0] == 'N' && img[1] == 'O')
		no_we_ea_textures(game, 'N', str);
	if (img[0] == 'W' && img[1] == 'E')
		no_we_ea_textures(game, 'W', str);
	if (img[0] == 'E' && img[1] == 'A')
		no_we_ea_textures(game, 'E', str);
	if (img[0] == 'S' && img[1] == 'O')
		so_sky_textures(game, 'S', str);
	if (img[0] == 'K' && img[1] == 'Y')
		so_sky_textures(game, 'K', str);
	if (img[0] == 'S' && img[1] == 'P')
		extract_sprite(game, str, chr);
	return ;
}
