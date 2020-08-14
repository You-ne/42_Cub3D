/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:33:11 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/12 08:05:23 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	*mlxp;
void	*winp;
int	x;	
int	y;


int	quit(int key, void *p)
{
	if (key == 0xFF1B)
		mlx_destroy_window(mlxp, winp);
}
int	redraw(void *p)
{
	x = 0;
	y = 0;
	while (x < 1360)
	{
		mlx_pixel_put(mlxp, winp, x, 384, 16777011);
		x++;
	}
	while (y < 768)
	{
		mlx_pixel_put(mlxp, winp, 690, y, 16777011);
		y++;
	}

}
int	main()
{
	x = 0;
	y = 0;
	mlxp = mlx_init();
	winp = mlx_new_window(mlxp, 1360, 768, "Dot");
	while (x < 1360)
	{
		mlx_pixel_put(mlxp, winp, x, 384, 16777011);
		x++;
	}
	while (y < 768)
	{
		mlx_pixel_put(mlxp, winp, 690, y, 16777011);
		y++;
	}
	mlx_key_hook(winp, quit, 0);
	mlx_expose_hook(winp, redraw, 0);
	mlx_loop(mlxp);
}
