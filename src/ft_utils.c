/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/05 04:38:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	extract_texture(t_game *game, char *str, char *img, char chr)
{
	char	*path;
	int fd;
	t_img *tex;
	t_img *tmp;

	printf("..%s..\n", img);
	while (*str == ' ')
		str++;
	path = ft_strdup(str);
	if (img[0] == 'N' && img[1] == 'O')
	{
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->NO.width, &game->NO.height);
		game->NO.img = mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
		game->NO.path = path;
	}
	if (img[0] == 'W' && img[1] == 'E')
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->WE.width, &game->WE.height);
		game->WE.img = mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
		game->WE.path = path;
}
	if (img[0] == 'E' && img[1] == 'A')
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->EA.width, &game->EA.height);
		game->EA.img = mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
		game->EA.path = path;
}
	if (img[0] == 'S' && img[1] == 'O')
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->SO.width, &game->SO.height);
		game->SO.img = mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
		game->SO.path = path;
	}
	if (img[0] == 'S' && img[1] == 'P')
	{
		if (chr == '2')
		{
			game->SP.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->SP.width, &game->SP.height);
			game->SP.img = mlx_get_data_addr(game->SP.img_p, &game->SP.bpp, &game->SP.s_line, &game->SP.endian);
			game->SP.path = path;
			game->SP.chr = '2';
			game->SP.next = NULL;
		}
		else
		{
			tmp = &game->SP;
			tex = (struct s_img*)malloc(sizeof(struct s_img));
			tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &tex->width, &tex->height);
			tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
			tex->path = path;
			tex->chr = chr;
			tex->next = NULL;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = tex;
		}
	}
	if (img[0] == 'S' && img[1] == 'K' && img[2] == 'Y')
	{
		game->SKY.img_p = mlx_xpm_file_to_image(game->win.mlxp, path, &game->SKY.width, &game->SKY.height);
		game->SKY.img = mlx_get_data_addr(game->SKY.img_p, &game->SKY.bpp, &game->SKY.s_line, &game->SKY.endian);
		game->SKY.path = path;
	}
	return ;
}
