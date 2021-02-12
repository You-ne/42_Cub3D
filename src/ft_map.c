/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/12 04:50:18 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

char	*count_sprites(t_game *game, int time, char *sp_set)
{
	int		i;
//	char	*sp_set;
	char	*tmp;
	t_img	*sp;

	if (time == 0)
		sp = &game->SP;
	else
		sp = &game->SA;
	while (sp->chr)
	{
		if (!(in_str(sp->chr, sp_set)))
		{
			tmp = ft_ctostr(1, sp->chr);
			sp_set = ft_strmcat(sp_set, tmp);
			free(tmp);
		}
		if (sp->next != NULL)
			sp = sp->next;
		else
			break;
	}
	return (sp_set);
}

int		verify_char(t_game *game, int y, int x, char *sp_set)
{
	if (in_str(game->map[y][x], sp_set) && (!game->map[y + 1] || !game->map[y][x + 1]))
		return (0);
	else if (in_str(game->map[y][x], sp_set) &&
	(game->map[y][x + 1] == ' ' || game->map[y][x - 1] == ' '
	|| game->map[y + 1][x] == ' ' || game->map[y - 1][x] == ' '))
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
				ft_error("Map not closed!\n", game);
			j++;
		}
		i++;
	}
}

void	get_map(t_game *game, int line, int nlines, char *sp_set) // good size
{
	char	**new;
	int		i;
	char	*new_set;

	i = 0;
	new_set = ft_strdup("1 ");
	new_set = ft_strmcat(new_set, sp_set);
	if(!(new = (char**)malloc(sizeof(char*) * (nlines + 1))))
		return;
	while(game->map[line] != NULL)
	{
		if (!is_str_charset(new_set, game->map[line]) || !in_str('1', game->map[line]))
			ft_error("Incorrect line in map layout!\n", game);
		new[i++] = ft_strdup(game->map[line++]);
	}
	new[i] = NULL;
	i = 0;
	while (game->map[i] != NULL)
		free(game->map[i++]);
	free(game->map);
	free(new_set);
	game->map = new;
}

void	find_map(t_game *game, int line) // good size
{
	int		end;
	char	*sp_set;
	char	*tmp_set;

	tmp_set = ft_strdup("NEWS0");
	tmp_set = count_sprites(game, 0, tmp_set);
	sp_set = count_sprites(game, 1, tmp_set);
	printf("SP_SET =%s !!!!!\n\n\n\n", sp_set);
	end = line;
	while(game->map[end] != NULL)
		end++;
	get_map(game, line, end - line, sp_set);
	verify_map(game, sp_set);
	free(sp_set);
}
