/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:19:45 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 01:12:59 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_clean_game(t_game *game)
{
	if (game->is_bmp == 0 && game->win_created == 1)
		mlx_destroy_window(game->win.mlxp, game->win.winp);
}

int		ft_exit(int keycode, t_game *game)
{
	if (game)
		ft_clean_game(game);
	exit(0);
	return (0);
}

void	ft_error(const char *str, t_game *game)
{
	ft_putstr_fd(str, 2);
	ft_exit(65307, game);
}
