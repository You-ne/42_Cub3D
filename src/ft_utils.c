/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 20:04:56 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	*extract_texture(t_game *game, char *str, char *img)
{
	int		i;
	char	*path;
	i = 0;
	while (str[i] != ' ')
		i++;
	if (!(path = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i] != ' ')
		path[i] = str[i++];
	path[i] = '\0';
	if (img == "NO")
	{
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->NO.width, game->NO.length);
		mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
		}
	if (img == "WE")
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->WE.width, game->WE.length);
		mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
		}
	if (img == "EA")
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->EA.width, game->EA.length);
		mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
		}
	if (img == "SO")
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, game->SO.width, game->SO.length);
		mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
		}
	return (path);
}
