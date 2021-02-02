/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/01/31 16:03:52 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

char	**extract_map(int fd)
{
	int	i;
	char	*tmp;
	char	**map;

	i = 0;
	/* gérer taille */
	if(!(map = (char**)malloc(sizeof(char*) * 1500)))
		return (NULL);
	while(get_next_line(fd, &tmp) > 0)
	{
		map[i] = ft_strdup_gnl(tmp);
		i++;
	}
	map[i] = NULL;
	return(map);
}

int	parser(t_game *game)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while(game->map[i] != NULL && k < 11)
	{
		j = 0;
		while(game->map[i][j] != '\0')
		{
			/* temporaire, rajouter détection mauvaises lignes */
			if (game->map[i][j] > 65 && game->map[i][j] < 91)
			{
				find_info(game->map[i], game);
				k++;
				break;
			}
			j++;
		}
		i++;
	}
	find_map(&game->map, i);

	printf("ResX = %d, ResY = %d\n", game->res[0], game->res[1]);
	printf("Floor: R = %d, G = %d, B = %d\n", (int)game->F[0],(int)game->F[1], (int)game->F[2]);
	printf("Ceiling: R = %d, G = %d, B = %d\n", (int)game->C[0],(int)game->C[1], (int)game->C[2]);
	printf("Floor Color = %d\nCeiling Color = %d\n", game->Fl, game->Ce);
	/* verification de t_game, renvoi d'erreur ? */
	return (0);
}

void	find_res(t_game *game)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while(game->map[i] != NULL)
	{
		j = 0;
		while(game->map[i][j] != '\0')
		{
			if (game->map[i][j] == 'R')
			{
				get_res(game->map[i], game);
				return;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_game	game;
	int		i;

	i = 0;
	if(argc ==  2)
	{
		fd = open(argv[1], O_RDONLY);
		game.map = extract_map(fd);
		close(fd);
		find_res(&game);
		game.win.mlxp = mlx_init();
		game.win.winp = mlx_new_window(game.win.mlxp, game.res[0], game.res[1], "Cub3D");
		printf("[START PARSING...]\n\n");
		parser(&game);
		game.player.pos = find_char(game.map);
		printf("\n[PARSING END!!!]\n");

		//Display map for debug
		printf("\nTRIMMED LAYOUT:\n");
		while (game.map[i] != NULL)
		{
			printf("%d:%s\n", i, game.map[i]);
			i++;
		}
		game.player.vect = init_dir(game.map, game.player.pos);
		ft_start_display(game);
	}
	return(0);
}
