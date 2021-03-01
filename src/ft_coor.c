/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 07:25:27 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/01 01:36:00 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void		start_found(t_coor *coor, t_game *game, int i, int j)
{
	if (game->start_found == 1)
		ft_error("Starting char appears twice on map!\n", game);
	else
	{
		coor->x = (double)(j) + 0.5;
		coor->y = (double)(i) + 0.5;
		coor->dist = 0;
		game->start_found = 1;
	}
}

t_coor		find_start(t_game *game)
{
	t_coor	coor;
	int	i;
	int	j;

	i = 0;
	if (game->map_found == 0)
		ft_error("Map layout not found in .cub file\n", game);
	while(game->map[i] != NULL)
	{
		j = 0;
		while(game->map[i][j] != '\0')
		{
			if(game->map[i][j] == 'N' || game->map[i][j] == 'S' 
					|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				start_found(&coor, game, i, j);
			j++;
		}
		i++;
	}
	return (coor);
}

t_coor		init_dir_2(char **map, t_coor coor)
{
	int		i;
	int		j;
	t_coor	vect;

	j = (int)(coor.x);
	i = (int)(coor.y);
	if (map[i][j] == 'W')
	{
		vect.x = -1;
		vect.y = 0;
		vect.dist = 0; 
	}
	else if (map[i][j] == 'E')
	{
		vect.x = 1;
		vect.y = 0;
		vect.dist = 0; 
	}
	return (vect);
}

t_coor		init_dir(char **map, t_coor coor)
{
	int		i;
	int		j;
	t_coor	vect;
	
	j = (int)(coor.x);
	i = (int)(coor.y);
	if (map[i][j] == 'N')
	{
		vect.x = 0;
		vect.y = -1;
		vect.dist = 0;
	}
	else if (map[i][j] == 'S')
	{
		vect.x = 0;
		vect.y = 1;
		vect.dist = 0;
	}
	else
		vect = init_dir_2(map, coor);
	return (vect);
}
