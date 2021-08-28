/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 01:52:24 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 20:20:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		verify_char(t_game *game, int y, int x, char *sp_set)
{
	if (in_str(game->map[y][x], sp_set) && (game->map[y + 1] == NULL || y == 0
	|| x == 0 || game->map[y][x] == '\0'))
		return (0);
	if (in_str(game->map[y][x], sp_set) && (game->map[y][x + 1] == ' ' ||
	game->map[y][x - 1] == ' ' || game->map[y + 1][x] == ' ' ||
	game->map[y - 1][x] == ' ' || game->map[y + 1][x + 1] == ' ' ||
	game->map[y - 1][x - 1] == ' ' || game->map[y - 1][x + 1] == ' ' ||
	game->map[y + 1][x - 1] == ' ' || game->map[y][x + 1] == '\0' ||
	game->map[y][x - 1] == '\0' || game->map[y + 1][x] == '\0' ||
	game->map[y - 1][x] == '\0' || game->map[y + 1][x + 1] == '\0' ||
	game->map[y - 1][x - 1] == '\0' || game->map[y - 1][x + 1] == '\0' ||
	game->map[y + 1][x - 1] == '\0'))
		return (0);
	return (1);
}

void	verify_map(t_game *game, char *sp_set)
{
	int		i;
	int		j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!verify_char(game, i, j, sp_set))
			{
				printf("y=%i, x=%i;\n", i, j);
				ft_error("Erreur: Map ouverte !\n", game);
			}
			j++;
		}
		i++;
	}
}

void	find_secret_door(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != 0)
		{
			if (game->map[y][x] == '*')
			{
				game->secret.x = x;
				game->secret.y = y;
				game->secret.dist = 1;
				return ;
			}
			x++;
		}
		y++;
	}
}

char	*count_sprites(t_game *game, int time, char *sp_set)
{
	char	*tmp;
	t_img	*sp;

	if (time == 0)
		sp = game->sp;
	else
		sp = game->sa;
	while (sp != NULL)
	{
		if (!(in_str(sp->chr, sp_set)))
		{
			tmp = ft_ctostr(1, sp->chr);
			sp_set = ft_strmcat(sp_set, tmp);
			free(tmp);
		}
		sp = sp->next;
	}
	return (sp_set);
}
