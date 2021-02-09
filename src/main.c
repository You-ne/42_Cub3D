/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/09 04:02:17 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	extract_file(char *path, t_game *game) // good length
{
	int		fd;
	int		i;
	int		size;
	char	*tmp;
	char	**map;

	i = 0;
	size = 0;
	fd = open(path, O_RDONLY);
	while(get_next_line(fd, &tmp) > 0)
	{
		free(tmp);
		size++;
	}
	close(fd);
	fd = open(path, O_RDONLY);
	if(!(game->map = (char**)malloc(sizeof(char*) * (size + 1))))
		ft_error("A problem occured during file extraction...\n", game);
	while(get_next_line(fd, &tmp) > 0)
	{
		game->map[i] = ft_strdup_gnl(tmp);
		i++;
		free(tmp);
	}
	game->map[i] = NULL;
}


int	parser(t_game *game) //too long
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while(game->map[i] != NULL)
	{
		j = 0;
		while(game->map[i][j] != '\0')
		{
			/* temporaire, rajouter détection mauvaises lignes */
			if (game->map[i][j] == '1')
			{
				if (k != NB_PARAMS)
					ft_error("Less parameters fetched than needed !! \n", game);
				find_map(game, i);
				return (0);
			}
			else if (game->map[i][j] > 65 && game->map[i][j] < 91)
			{
				k++;
				if (k > NB_PARAMS)
					ft_error("Too much parameters !!\n", game);
				find_info(game->map[i], game);
				break;
			}
			else if (game->map[i][j] == ' ')
				j++;
			else
				ft_error("Invalid map line\n\n", game);
		}
		i++;
	}
if (k < NB_PARAMS)
	ft_error("Not enough parameters!! \n", game);
	return (0);
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
				get_res(game->map[i], game); //may change get_res
				return;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
//	int		fd;
	t_game	game;
	int		i;

	i = 0;
	check_args(&game, argv, argc);
	check_fd(&game, argv[1]);
	extract_file(argv[1], &game);
	find_res(&game);
	game.win.mlxp = mlx_init();
	game.win.winp = mlx_new_window(game.win.mlxp, game.res[0], game.res[1], "Cub3D");
	parser(&game);
	game.player.pos = find_char(game.map);
	//change_map(&game, (int)game.player.pos.x, (int)game.player.pos.y, '0');
	game.player.weapon = get_weapon(&game);
	game.player.pv = 100.0;

	//Display map for debug
	printf("\nTRIMMED LAYOUT:\n");
	while (game.map[i] != NULL)
	{
		printf("%d:%s\n", i, game.map[i]);
		i++;
	}
	game.player.vect = init_dir(game.map, game.player.pos);
	ft_start_display(game);
	return(0);
}
