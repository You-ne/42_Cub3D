/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/18 23:25:02 by antoine          ###   ########.fr       */
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

void	add_enemy(int x, int y, char enemy_chr, t_game *game)
{
	t_enemy		*tmp;

	tmp = game->enemies;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_enemy*)malloc(sizeof(t_enemy));
	tmp = tmp->next;
	tmp->x = x;
	tmp->y = y;
	tmp->fire = 0;
	if (enemy_chr == '@')
	{
		tmp->pv = 70;
		tmp->damage = -10;
		tmp->time_anim = 200;
	}
	else if (enemy_chr == '#')
	{
		tmp->pv = 100;
		tmp->damage = -10;
		tmp->time_anim = 50;
	}
	else if (enemy_chr == '!')
	{
		tmp->pv = 180;
		tmp->damage = -10;
		tmp->time_anim = 150;
	}
	else if (enemy_chr == 'M')
	{
		tmp->pv = 200;
		tmp->damage = -10;
		tmp->time_anim = 80;
	}
	else if (enemy_chr == 'H')
	{
		tmp->pv = 180;
		tmp->damage = -10;
		tmp->time_anim = 120;
	}
	tmp->chr = enemy_chr;
//	tmp->tdeath = 0;
	tmp->next = NULL;
}

void	get_enemies(t_game *game, char *foes_set)
{
	int		x;
	int		y;
	t_enemy	*tmp;

	y = 0;
	game->enemies = (t_enemy*)malloc(sizeof(t_enemy));
	game->enemies->next = NULL;
	game->enemies->x = -1;
	game->enemies->chr = '0';
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != 0)
		{
			if (in_str(game->map[y][x], foes_set))
			{
				add_enemy(x, y, game->map[y][x], game);
				if (game->map[y][x] == 'M')
					add_enemy(x, y, 'H', game);
			}
			x++;
		}
		y++;
	}
	free(foes_set);
	tmp = game->enemies;
	while (tmp->next != NULL)
	{
		printf("ENEMY : %c \n", tmp->chr);
		tmp = tmp->next;
	}
}

char	*get_foes_char(t_img *enemies)
{
	t_img	*tmp;
	char	*set;
	char	*chr;

	tmp = enemies;
	set = ft_strdup("");
	while (tmp->next != NULL)
	{
		if (!(in_str(tmp->chr, set)))
		{
			chr = ft_ctostr(1, tmp->chr);
			set = ft_strmcat(set, chr);
			free(chr);
		}
		tmp = tmp->next;
	}
	return (set);
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
	get_enemies(game, get_foes_char(&game->SA));
	free(sp_set);
}
