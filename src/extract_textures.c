/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 04:23:43 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:06:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_xpm(t_game *game, t_img *tex, char *str)
{
	tex->img_p = mlx_xpm_file_to_image(game->win.mlxp, str,
	&tex->width, &tex->height);
	if (tex->img_p == NULL)
		ft_error("Troubles extracting texture !\n", game);
	tex->img = mlx_get_data_addr(tex->img_p, &tex->bpp,
	&tex->s_line, &tex->endian);
}

t_img	*find_sprite(t_game *game, char chr)
{
	t_img *tex1;
	t_img *tex2;

	tex1 = game->sp;
	tex2 = game->sa;
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
	return (NULL);
}

void	extract_sprite(t_game *game, char *str, char chr, t_img *sp_sa)
{
	t_img	*tmp;
	t_img	*tex;

	if ((sp_sa == game->sa && sp_sa->chr == '0') ||
	(sp_sa == game->sp && sp_sa->chr == '2'))
	{
		extract_xpm(game, sp_sa, str);
		sp_sa->chr = chr;
	}
	else
	{
		tmp = sp_sa;
		if (!(tex = (struct s_img*)malloc(sizeof(struct s_img))))
			ft_error("Erreur: Malloc a échoué !\n", game);
		extract_xpm(game, tex, str);
		tex->chr = chr;
		tex->next = NULL;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tex;
	}
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
	extract_xpm(game, w, n1);
	extract_xpm(game, w2, n2);
	extract_xpm(game, w3, n3);
	w->next = w2;
	w2->next = w3;
	w3->next = 0x0;
	return (w);
}
