/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2021/01/08 00:08:24 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	*extract_texture(t_game *game, char *str, char *img)
{
	char	*path;
	int fd;
	char **tex;


	while (*str == ' ')
		str++;
	path = ft_strdup(str);
	printf("win.mlxp = %p\n", game->win.mlxp);
	printf("EXTRACTING TEXTURES...\n\n");
	printf("IMG = %s\n\n", img);
	printf("Path: %s\n\n", path);
	printf("win.mlxp = %p\n", game->win.mlxp);
	if (img[0] == 'N' && img[1] == 'O')
	{
		printf("NO texture :");
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->NO.width, &game->NO.height);
		game->NO.img = mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
	}
	if (img[0] == 'W' && img[1] == 'E')
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->WE.width, &game->WE.height);
		game->WE.img = mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
		printf("AA%sAA\n\n", game->WE.img);
	}
	if (img[0] == 'E' && img[1] == 'A')
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->EA.width, &game->EA.height);
		game->EA.img = mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
		printf("AA%sAA\n\n", game->EA.img);
	}
	if (img[0] == 'S' && img[1] == 'O')
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->SO.width, &game->SO.height);
		game->SO.img = mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
		printf("AA%sAA\n\n", game->SO.img);
	}
	return (path);
}
