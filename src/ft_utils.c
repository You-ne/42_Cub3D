/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 22:12:41 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	*extract_texture(t_game *game, char *str, char *img)
{
	int		i;
	char	*path;
	int *a;
	int *b;
	
	*a = 64;
	*b = 64;
	while (*str == ' ')
		str++;
	path = ft_strdup(str);
	printf("EXTRACTING TEXTURES...\n\n");
	printf("IMG = %s\n\n", img);
	printf("Path: %s\n\n", path);
	if (img[0] == 'N' && img[1] == 'O')
	{
		printf("NO texture :");
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, a, b);
		//game->NO.img = mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
		//printf("%s\n\n", game->NO.img);
	}
	if (img[0] == 'W' && img[1] == 'E')
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->WE.width, game->WE.height);
		game->WE.img = mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
		}
	if (img[0] == 'E' && img[1] == 'A')
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->EA.width, game->EA.height);
		game->EA.img = mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
	}
	if (img[0] == 'S' && img[1] == 'O')
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->SO.width, game->SO.height);
		game->SO.img = mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
	}
	return (path);
}
