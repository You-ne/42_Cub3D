/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 07:25:27 by yotillar          #+#    #+#             */
/*   Updated: 2020/11/24 00:40:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_coor	find_char(char **map)
{
	t_coor coor;
	int	i;
	int	j;

	i = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if(map[i][j] == 'N' || map[i][j] == 'S' 
					|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				coor.x = (double)(j) + 0.5;
				coor.y = (double)(i) + 0.5;
				coor.dist = 0;
				return (coor);
			}
			j++;
		}
		i++;
	}
}

t_coor init_dir(char **map, t_coor coor)
{
	int	i;
	int	j;
	t_coor	vect;
	
	j = (int)(coor.x);
	i = (int)(coor.y);
	if(map[i][j] == 'N')
	{
		vect.x = 0;
		vect.y = -1;
		vect.dist = 0;
	}
	if(map[i][j] == 'S') 
	{
		vect.x = 0;
		vect.y = 1;
		vect.dist = 0; 
	}

	if(map[i][j] == 'W')
	{
		vect.x = -1;
		vect.y = 0;
		vect.dist = 0; 
	}

	if(map[i][j] == 'E')
	{
		vect.x = 1;
		vect.y = 0;
		vect.dist = 0; 
	}
	return (vect);
}
