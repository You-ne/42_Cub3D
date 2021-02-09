/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/08 23:28:48 by antoine          ###   ########.fr       */
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
	while(game->map[i] != NULL && k < 12)
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

t_img	*get_weapon(t_game *game)
{
	t_img *weapon;
	t_img *weapon2;
	t_img *weapon3;

	weapon = (struct s_img*)malloc(sizeof(struct s_img));
	weapon2 = (struct s_img*)malloc(sizeof(struct s_img));
	weapon3 = (struct s_img*)malloc(sizeof(struct s_img));

	weapon->img_p = mlx_xpm_file_to_image(game->win.mlxp, "./sprites/M2GFB0.xpm", &weapon->width, &weapon->height);
	weapon->img = mlx_get_data_addr(weapon->img_p, &weapon->bpp, &weapon->s_line, &weapon->endian);
	weapon2->img_p = mlx_xpm_file_to_image(game->win.mlxp, "./sprites/M2GFA0.xpm", &weapon2->width, &weapon2->height);
	weapon2->img = mlx_get_data_addr(weapon2->img_p, &weapon2->bpp, &weapon2->s_line, &weapon2->endian);
	weapon3->img_p = mlx_xpm_file_to_image(game->win.mlxp, "./sprites/M2GFC0.xpm", &weapon3->width, &weapon3->height);
//	printf("weapon3=%p\n", weapon3->img_p);
	weapon3->img = mlx_get_data_addr(weapon3->img_p, &weapon3->bpp, &weapon3->s_line, &weapon3->endian);
	weapon->next = weapon2;
	weapon2->next = weapon3;
	weapon3->next = 0x0;
	return (weapon);
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
//		change_map(&game, (int)game.player.pos.x, (int)game.player.pos.y, '0');
		game.player.pv = 100.0;
		game.player.weapon = get_weapon(&game);
		printf("X=%f; Y=%f\n", game.player.pos.x, game.player.pos.y);
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
