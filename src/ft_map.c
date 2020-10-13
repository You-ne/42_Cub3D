/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 21:00:54 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"


void	free_map(char ***old_map)
{
	free(old_map[0][1]);
	free(*old_map);
}

/*void	verify_map(char ***map, t_coor * coor);*/

void	get_map(char ***map, int line, int nlines)
{
	/** gére erreurs malloc */
	char	***new;
	char	***tmp;
	int	i;

	i = 0;
	if(!(new = (char***)malloc(sizeof(char**) * 1)))
		return;
	if(!(*new = (char**)malloc(sizeof(char*) * (nlines + 1))))
		return;
	while(map[0][line] != NULL)
	{
		new[0][i++] = ft_strdup(map[0][line++]);
	}
	new[0][i] = NULL;
	*tmp = *map;
	map[0] = new[0];
	free_map(tmp);
}

void	find_map(char ***map, int line)
{
	int	end;
	int	i;

	i = 0;
	line++;
	while(map[0][line][i] != '\0')
	{
		printf("%d\n", i);
		if(map[0][line][i] == '1')
		{
			end = line;
			while(map[0][end] != NULL)
				end++;
			get_map(map, line, end - line);
			/*	verify_map(map, coor);*/
			return;
		}
		i++;
	}
	line++;
}
