/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 06:04:14 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/25 09:34:41 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

char	*count_sprites(t_game *game, int time, char *sp_set) //norme
{
	int		i;
	char	*tmp;
	t_img	*sp;

	if (time == 0)
		sp = game->SP;
	else
		sp = game->SA;
	while (sp->next != NULL)
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

int		verify_char(t_game *game, int y, int x, char *sp_set) //norme
{
	if (in_str(game->map[y][x], sp_set) && (!game->map[y + 1] || !game->map[y][x + 1]))
		return (0);
	if (in_str(game->map[y][x], sp_set) && (game->map[y][x + 1] == ' ' || game->map[y][x - 1] == ' ' || game->map[y + 1][x] == ' ' || game->map[y - 1][x] == ' '))
		return (0);
	return (1);
}

void	verify_map(t_game *game, char *sp_set) //norme
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
		ft_error("Problem occured during map allocation\n", game);
	while(game->map[line] != NULL)
	{
		if (!is_str_charset(new_set, game->map[line]) || !in_str('1', game->map[line]))
			ft_error("Incorrect line in map layout!\n", game);
		new[i] = ft_strdup(game->map[line++]);
		if (!(new[i++]))
			ft_error("Trouble allocating a map line\n", game);
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
	if (tmp->x != -1)
	{
		tmp->next = (t_enemy*)malloc(sizeof(t_enemy));
		tmp = tmp->next;
	}
	tmp->x = x;
	tmp->y = y;
	tmp->fire = 0;
	param_enemy(game, tmp, enemy_chr);
	tmp->chr = find_shooting_chr(enemy_chr);
	tmp->next = NULL;
}

void	get_enemies(t_game * game, char *foes_set)
{
	int		x;
	int		y;
	t_enemy *tmp;

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
	while (tmp)
	{
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
				return;
			}
			x++;
		}
		y++;
	}
}

int		find_map(t_game *game, int line, int nb_params) // good size
{
	int		end;
	char	*sp_set;
	char	*tmp_set;

	if (game->nb_params > NB_PARAMS || game->nb_params < NB_PARAMS)
		ft_error("Too much or not enough parameters in .cub file\n\n", game);
	tmp_set = ft_strdup("NEWS0");
	tmp_set = count_sprites(game, 0, tmp_set);
	sp_set = count_sprites(game, 1, tmp_set);
	printf("SP_SET =%s !!!!!\n\n\n\n", sp_set);
	end = line;
	while(game->map[end] != NULL)
		end++;
	get_map(game, line, end - line, sp_set);
	verify_map(game, sp_set);
	get_enemies(game, get_foes_char(game->SA));
	find_secret_door(game);
	free(sp_set);
	game->map_found = 1;
	return (1);
}
