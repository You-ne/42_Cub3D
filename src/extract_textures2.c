/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_textures2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 04:23:43 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 17:17:04 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_img	*find_sprite(t_game *game, char chr)
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
	void	*p;
	char	*s;

	tmp = game->SA;
	if (!(tex = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	p = mlx_xpm_file_to_image(game->win.mlxp, str, &tex->width, &tex->height);
	tex->img_p = p;
	if (!(game->SA->img_p))
		ft_error("Troubles extracting sprites textures !!\n", game);
	s = mlx_get_data_addr(tex->img_p, &tex->bpp, &tex->s_line, &tex->endian);
	tex->img = s;
	tex->chr = chr;
	tex->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = tex;
}

void	extract_anim(t_game *game, char *str, char chr)
{
	if (game->SA->chr == '0')
	{
		game->SA->img_p = mlx_xpm_file_to_image(game->win.mlxp, str,
		&game->SA->width, &game->SA->height);
		if (!(game->SA->img_p))
			ft_error("Troubles extracting sprites textures !!\n", game);
		game->SA->img = mlx_get_data_addr(game->SA->img_p, &game->SA->bpp,
		&game->SA->s_line, &game->SA->endian);
		game->SA->chr = chr;
	}
	else
		extract_anim2(game, str, chr);
}

void	extract_texture(t_game *game, char *str, char *img, char chr)
{
	if (img[0] == 'N' && img[1] == 'O')
		no_we_textures(game, 'N', str);
	if (img[0] == 'W' && img[1] == 'E')
		no_we_textures(game, 'W', str);
	if (img[0] == 'E' && img[1] == 'A')
		so_ea_textures(game, 'E', str);
	if (img[0] == 'S' && img[1] == 'O')
		so_ea_textures(game, 'S', str);
	if (img[0] == 'K' && img[1] == 'Y')
		sky_texture(game, 'K', str);
	if (img[0] == 'S' && img[1] == 'P')
		extract_sprite(game, str, chr);
	return ;
}

t_img	*get_weapon_tex(t_game *game, char *n1, char *n2, char *n3)
{
	t_img *w;
	t_img *w2;
	t_img *w3;

	if (!(w = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	if (!(w2 = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	if (!(w3 = (struct s_img*)malloc(sizeof(struct s_img))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	w->img_p = mlx_xpm_file_to_image(game->win.mlxp, n1, &w->width, &w->height);
	w->img = mlx_get_data_addr(w->img_p, &w->bpp, &w->s_line, &w->endian);
	w2->img_p = mlx_xpm_file_to_image(game->win.mlxp, n2, &w2->width,
	&w2->height);
	w2->img = mlx_get_data_addr(w2->img_p, &w2->bpp, &w2->s_line, &w2->endian);
	w3->img_p = mlx_xpm_file_to_image(game->win.mlxp, n3, &w3->width,
	&w3->height);
	w3->img = mlx_get_data_addr(w3->img_p, &w3->bpp,
	&w3->s_line, &w3->endian);
	w->next = w2;
	w2->next = w3;
	w3->next = 0x0;
	return (w);
}
