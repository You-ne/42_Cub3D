/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_textures2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 04:23:43 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/27 04:44:25 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_img *find_sprite(t_game *game, char chr)
{
	t_img *tex1;
	t_img *tex2;

	tex1 = game->SP;
	tex2 = game->SA;
	while (tex1->chr != chr && tex1->next != NULL)
	{
		tex1 = tex1->next;
	}
	if (tex1->chr == chr)
		return (tex1);
	while (tex2->chr != chr && tex2->next != NULL)
	{
		tex2 = tex2->next;
	}
	if (tex2->chr == chr)
		return (tex2);
}



void	extract_anim2(t_game *game, char *str, char chr)
{
	t_img	*tmp;
	t_img	*tex;


	tmp = game->SA;
	tex = (struct s_img*)malloc(sizeof(struct s_img));
	tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, str, &tex->width, &tex->height);
	if (!(game->SA->img_p))
		ft_error("Troubles extracting sprites textures !!\n", game);
	tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
	tex->chr = chr;
	tex->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = tex;
}

void	extract_anim(t_game *game, char *str, char chr)
{
	if (game->SA->chr == '1')
	{

		game->SA->img_p = mlx_xpm_file_to_image(game->win.mlxp, str,
		&game->SA->width, &game->SA->height);
		if (!(game->SA->img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		game->SA->img = mlx_get_data_addr(game->SA->img_p, &game->SA->bpp,
		&game->SA->s_line, &game->SA->endian);
		game->SA->chr = chr;
		game->SA->next = NULL;
	}
	else
		extract_anim2(game, str, chr);
}


