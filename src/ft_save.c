/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 05:17:21 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/01 01:36:57 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_bmp	init_bmp(t_game *game)
{
	t_bmp	bmp;

	bmp.zero = 0;
	bmp.size = game->res[0] * game->res[1] * 4;
	bmp.offset = 54;
	bmp.dib_size = 40;
	bmp.width = game->res[0];
	bmp.heigth = game->res[1];
	bmp.planes = 1;
	bmp.bpp = 32;
	return (bmp);
}

int	bmp_header(int fd, t_bmp *bmp)
{
	if (write(fd, &"BM", 2) == -1)
		return (-1);
	if (write(fd, &bmp->size, 4) == -1)
		return (-1);
	if (write(fd, &bmp->zero, 4) == -1)
		return (-1);
	if (write(fd, &bmp->offset, 4) == -1)
		return (-1);
	if (write(fd, &bmp->dib_size, 4) == -1)
		return (-1);
	if (write(fd, &bmp->width, 4) == -1)
		return (-1);
	if (write(fd, &bmp->heigth, 4) == -1)
		return (-1);
	if (write(fd, &bmp->planes, 2) == -1)
		return (-1);
	if (write(fd, &bmp->bpp, 2) == -1)
		return (-1);
	if (write(fd, &bmp->zero, 8) == -1)
		return (-1);
	if (write(fd, &bmp->zero, 8) == -1)
		return (-1);
	if (write(fd, &bmp->zero, 8) == -1)
		return (-1);
	return (1);
}

int	bmp_img(t_bmp *bmp, int fd, t_img *img)
{
	int		x;
	int		y;

	y = bmp->heigth;
	while (y > 0)
	{
		x = 0;
		while (x < bmp->width)
		{
			if (write(fd, &img->img[((y * bmp->width) -
			(bmp->width - x)) * 4], 4) == -1)
				return (-1);
			x++;
		}
		y--;
	}
	return (1);
}

void	save(t_game *game, t_img *img)
{
	int		fd;
	t_bmp	bmp;

	if ((fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		ft_error("Cannot create .bmp file!\n", game);
	bmp = init_bmp(game);
	if (bmp_header(fd, &bmp) == -1)
		ft_error("Erreur: write a échoué !\n", game);
	if (bmp_img(&bmp, fd, img) == -1)
		ft_error("Erreur: write a échoué :\n", game);
	close(fd);
	ft_exit(65307, game);
}
