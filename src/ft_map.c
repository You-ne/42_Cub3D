/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/11 03:06:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

int		verify_char(t_game *game, int y, int x)
{
	if (in_str(game->map[y][x], "NEWS02345@Pp") && (!game->map[y + 1] || !game->map[y][x + 1]))
		return (0);
	else if (in_str(game->map[y][x], "NEWS02345@Pp") &&
	(game->map[y][x + 1] == ' ' || game->map[y][x - 1] == ' '
	|| game->map[y + 1][x] == ' ' || game->map[y - 1][x] == ' '))
		return (0);
	return (1);
}

void	verify_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!verify_char(game, i, j))
				ft_error("Map not closed!\n", game);
			j++;
		}
		i++;
	}
}

void	get_map(t_game *game, int line, int nlines) // good size
{
	char	**new;
	int	i;

	i = 0;
	if(!(new = (char**)malloc(sizeof(char*) * (nlines + 1))))
		return;
	while(game->map[line] != NULL)
	{
		if (!is_str_charset(" NEWS012345@Pp", game->map[line]) || !in_str('1', game->map[line]))
			ft_error("Incorrect line in map layout!\n", game);
		new[i++] = ft_strdup(game->map[line++]);
	}
	new[i] = NULL;
	i = 0;
	while (game->map[i] != NULL)
		free(game->map[i++]);
	free(game->map);
	game->map = new;
}

void	find_map(t_game *game, int line) // good size
{
	int		end;

	end = line;
	while(game->map[end] != NULL)
		end++;
	get_map(game, line, end - line);
	verify_map(game);
}
