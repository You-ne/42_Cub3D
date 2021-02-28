/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 20:13:46 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void		extract_file(char *path, t_game *game)
{
	int		fd;
	int		i;
	int		size;
	char	*tmp;
	char	**map;

	i = 0;
	size = 0;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		free(tmp);
		size++;
	}
	close(fd);
	fd = open(path, O_RDONLY);
	if (!(game->map = (char**)malloc(sizeof(char*) * (size + 1))))
		ft_error("Erreur: Malloc a échoué !\n", game);
	while (get_next_line(fd, &tmp) > 0)
	{
		game->map[i] = ft_strdup_gnl(tmp);
		i++;
		free(tmp);
	}
	game->map[i] = NULL;
}

int			parser(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == '1')
				return (find_map(game, i, game->nb_params));
			if (game->map[i][j] > 65 && game->map[i][j] < 91)
			{
				game->nb_params++;
				find_info(game->map[i], game);
				break ;
			}
			else if (game->map[i][j] == ' ')
				j++;
			else
				ft_error("Erreur: Ligne invalide dans le fichier .cub\n", game);
		}
		i++;
	}
	return (0);
}

void		find_res(t_game *game)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'R')
			{
				game->found[7] = 1;
				get_res(&game->map[i][j + 1], game);
				return ;
			}
			j++;
		}
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_game	game;
	int		i;

	i = 0;
	init(&game);
	init_keys(&game);
	check_args(&game, argv, argc);
	check_fd(&game, argv[1]);
	extract_file(argv[1], &game);
	game.win.mlxp = mlx_init();
	find_res(&game);
	if (!(parser(&game) == 1))
		ft_error("Map not found!\n", &game);
	game.player.pos = find_char(&game);
	game.player.weapon = get_weapon_tex(&game, P1, P2, P3);
	game.player.weapon2 = get_weapon_tex(&game, M1, M2, M3);
	game.enemy_fire_t1 = clock();
	init_screens(&game);
	change_map(&game, (int)game.player.pos.x, (int)game.player.pos.y, '0');
	ft_start_display(&game);
	return (0);
}
