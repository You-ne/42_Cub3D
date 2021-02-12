/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 08:33:08 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/12 03:54:25 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	extract_anim(t_game *game, char *str, char chr)
{
	t_img	*tmp;
	t_img	*tex;
	
	printf("Trying to extract anim at :%s\n\n", str);
	if (game->SA.chr == '1')
	{
		game->SA.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SA.width, &game->SA.height);
		if (!(game->SA.img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		game->SA.img = mlx_get_data_addr(game->SA.img_p, &game->SA.bpp, &game->SA.s_line, &game->SA.endian);
		//game->SP.path = path;
		game->SA.chr = chr;
		game->SA.next = NULL;
	}
	else
	{
		tmp = &game->SA;
		tex = (struct s_img*)malloc(sizeof(struct s_img));
		tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &tex->width, &tex->height);
		if (!(game->SA.img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
		//tex->path = path;
		tex->chr = chr;
		tex->next = NULL;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tex;
	}
}

void	extract_texture(t_game *game, char *str, char *img, char chr)
{
	char	*path;
	int fd;
	t_img *tex;
	t_img *tmp;

	//printf("..%s..\n", img);
	/*	while (*str == ' ') inutile?
		str++;*/
	//path = ft_strdup(str);
	if (img[0] == 'N' && img[1] == 'O')
	{
		game->NO.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->NO.width, &game->NO.height);
		if (!(game->NO.img_p))
			ft_error("Troubles extracting NO texture !!\n", game);
		game->NO.img = mlx_get_data_addr(game->NO.img_p, &game->NO.bpp, &game->NO.s_line, &game->NO.endian);
		//game->NO.path = path;
	}
	if (img[0] == 'W' && img[1] == 'E')
	{
		game->WE.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->WE.width, &game->WE.height);
		if (!(game->WE.img_p))
			ft_error("Troubles extracting WE texture !!\n", game);
		game->WE.img = mlx_get_data_addr(game->WE.img_p, &game->WE.bpp, &game->WE.s_line, &game->WE.endian);
		//game->WE.path = path;
	}
	if (img[0] == 'E' && img[1] == 'A')
	{
		game->EA.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->EA.width, &game->EA.height);
		if (!(game->EA.img_p))
			ft_error("Troubles extracting EA texture !!\n", game);
		game->EA.img = mlx_get_data_addr(game->EA.img_p, &game->EA.bpp, &game->EA.s_line, &game->EA.endian);
		//game->EA.path = path;
	}
	if (img[0] == 'S' && img[1] == 'O')
	{
		game->SO.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SO.width, &game->SO.height);
		if (!(game->SO.img_p))
			ft_error("Troubles extracting SO texture !!\n", game);
		game->SO.img = mlx_get_data_addr(game->SO.img_p, &game->SO.bpp, &game->SO.s_line, &game->SO.endian);
		//game->SO.path = path;
	}
	if (img[0] == 'S' && img[1] == 'P')
	{
		if (chr == '2')
		{
			game->SP.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SP.width, &game->SP.height);
			if (!(game->SP.img_p))
				ft_error("Troubles extracting sprites textures !!\n", game);
			game->SP.img = mlx_get_data_addr(game->SP.img_p, &game->SP.bpp, &game->SP.s_line, &game->SP.endian);
			//game->SP.path = path;
			game->SP.chr = '2';
			game->SP.next = NULL;
		}
		else
		{
			tmp = &game->SP;
			tex = (struct s_img*)malloc(sizeof(struct s_img));
			tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &tex->width, &tex->height);
			if (!(game->SP.img_p))
				ft_error("Troubles extracting sprites textures !!\n", game);
			tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
			//tex->path = path;
			tex->chr = chr;
			tex->next = NULL;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = tex;
		}
	}
	if (img[0] == 'K' && img[1] == 'Y')
	{
		game->SKY.img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &game->SKY.width, &game->SKY.height);
		if (!(game->SKY.img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);

		game->SKY.img = mlx_get_data_addr(game->SKY.img_p, &game->SKY.bpp, &game->SKY.s_line, &game->SKY.endian);
	}
	return ;
}

int		is_str_charset(char *charset, char *str)
{
	int		i;
	int		j;

	i = 0;
	if (!str || !str[i] || !charset)
		return (0);
	while (str[i])
	{
		j = 0;
		while (charset[j] && (charset[j] != str[i]))
			j++;
		if (!charset[j])
			return (0);
		i++;
	}
	return (1);
}

int		in_str(char c, char *str)
{
	int		i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
