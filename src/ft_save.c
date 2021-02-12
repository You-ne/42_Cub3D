/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 05:17:21 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/12 00:17:15 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

t_bmp		init_bmp(t_game *game)
{
	t_bmp bmp;

	bmp.zero = 0;
	bmp.size = game->res[0] * game->res[1] * 4;
	printf("1st BMP SIZE = %d\n", bmp.size);
	bmp.offset = 54;
	bmp.dib_size = 40;
	bmp.width = game->res[0];
	bmp.heigth = game->res[1];
	bmp.planes = 1;
	bmp.bpp = 32;
	return (bmp);
}

void		bmp_header(int fd, t_bmp *bmp)
{
	write(fd, &"BM", 2);
	write(fd, &bmp->size, 4);
	write(fd, &bmp->zero, 4);
	write(fd, &bmp->offset, 4);
	write(fd, &bmp->dib_size, 4);
	write(fd, &bmp->width, 4);
	write(fd, &bmp->heigth, 4);
	write(fd, &bmp->planes, 2);
	write(fd, &bmp->bpp, 2);
	write(fd, &bmp->zero, 8);
	write(fd, &bmp->zero, 8);
	write(fd, &bmp->zero, 8);
}

void		bmp_img(t_bmp *bmp, int fd, t_img *img)
{
	int		x;
	int		y;
	//int		pixels;
	int		l;
	y = bmp->heigth;
//	pixels = bmp->size / 4;
	l = ft_strlen(img->img);
	printf("W =  %d\n Y = %d\n", bmp->width, bmp->heigth);
/*	while(pixels > 0)
	{
		write(fd, &img->img[(pixels * 4) - 4], 4);
		pixels--;
	}*/
	while (y > 0)
	{
		x = 0;
		while (x < bmp->width)
		{
			write(fd, &img->img[((y * bmp->width) - (bmp->width - x)) * 4], 4);
			x++;
		}
		y--;
	}
	
}

void		save(t_game *game, t_img *img)
{
	int		fd;
	t_bmp	bmp;

	if ((fd = open("save.bmp", O_WRONLY | O_CREAT | O_TRUNC , 0644)) < 0)
		ft_error("Cannot create .bmp file!\n", game);

	printf("Res of Window in pixels %d x %d = %d\nRepresented by %d chars\n", game->res[0], game->res[1], game->res[0] * game->res[1], game->res[0] * game->res[1] * 4);


	bmp = init_bmp(game);
	bmp_header(fd, &bmp);
	bmp_img(&bmp, fd, img);
	close(fd);
	printf("End of Save\n");
	ft_exit(65307, game);
 }
