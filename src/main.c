/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/22 02:52:55 by antoine          ###   ########.fr       */
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
/*
void	get_door_tex(t_game *game)
{
	t_img *door;
	t_img *door2;
	t_img *tmp;

	tmp = &game->SP;
	door = (struct s_img*)malloc(sizeof(struct s_img));
	door2 = (struct s_img*)malloc(sizeof(struct s_img));

	door->img_p = mlx_xpm_file_to_image(game->win.mlxp, D1, &door->width, &door->height);
	door->img = mlx_get_data_addr(door->img_p, &door->bpp, &door->s_line, &door->endian);
	door2->img_p = mlx_xpm_file_to_image(game->win.mlxp, D2, &door2->width, &door2->height);
	door2->img = mlx_get_data_addr(door2->img_p, &door2->bpp, &door2->s_line, &door2->endian);
	door->next = door2;
	door2->next = NULL;
	door->chr = 'P';
	door2->chr = 'p';
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = door;
}
*/
/*
void	get_enemy_tex(t_game *game)
{
	t_img *enemy;
	t_img *enemy2;
	t_img *tmp;

	tmp = &game->SP;
	enemy = (struct s_img*)malloc(sizeof(struct s_img));
	enemy2 = (struct s_img*)malloc(sizeof(struct s_img));

	enemy->img_p = mlx_xpm_file_to_image(game->win.mlxp, E1, &enemy->width, &enemy->height);
	printf("img_p=%p\n", enemy->img_p);
	enemy->img = mlx_get_data_addr(enemy->img_p, &enemy->bpp, &enemy->s_line, &enemy->endian);
	enemy2->img_p = mlx_xpm_file_to_image(game->win.mlxp, E2, &enemy2->width, &enemy2->height);
	printf("img_p=%p\n", enemy2->img_p);
	enemy2->img = mlx_get_data_addr(enemy2->img_p, &enemy2->bpp, &enemy2->s_line, &enemy2->endian);
	enemy->next = enemy2;
	enemy2->next = NULL;
	enemy->chr = '@';
	enemy2->chr = '@';
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = enemy;
}
*/
t_img	*get_weapon_tex(t_game *game)
{
	t_img *weapon;
	t_img *weapon2;
	t_img *weapon3;

	weapon = (struct s_img*)malloc(sizeof(struct s_img));
	weapon2 = (struct s_img*)malloc(sizeof(struct s_img));
	weapon3 = (struct s_img*)malloc(sizeof(struct s_img));

	weapon->img_p = mlx_xpm_file_to_image(game->win.mlxp, W1, &weapon->width, &weapon->height);
	weapon->img = mlx_get_data_addr(weapon->img_p, &weapon->bpp, &weapon->s_line, &weapon->endian);
	weapon2->img_p = mlx_xpm_file_to_image(game->win.mlxp, W2, &weapon2->width, &weapon2->height);
	weapon2->img = mlx_get_data_addr(weapon2->img_p, &weapon2->bpp, &weapon2->s_line, &weapon2->endian);
	weapon3->img_p = mlx_xpm_file_to_image(game->win.mlxp, W3, &weapon3->width, &weapon3->height);
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
	game.SA.chr = '1';
	parser(&game);
	game.player.pos = find_char(game.map);
	game.player.weapon = get_weapon_tex(&game);
	game.player.num_weapon = 1;
	game.player.damage = -40;
	//get_enemy_tex(&game);
//	get_door_tex(&game);
//	while (game.SP.next != NULL)
//	{
//		printf("SP=%c;\n", game.SP.chr);
//		game.SP = *(game.SP.next);
//	}
//	printf("SP=%c;\n", game.SP.chr);
	game.player.pv = 100.0;
	game.tilt = 0;
	game.enemy_fire_t1 = clock();
	game.game_over.img_p = mlx_xpm_file_to_image(game.win.mlxp, GAME_OVER, &game.game_over.width, &game.game_over.height);
	game.game_over.img = mlx_get_data_addr(game.game_over.img_p, &game.game_over.bpp, &game.game_over.s_line, &game.game_over.endian);
	game.you_win.img_p = mlx_xpm_file_to_image(game.win.mlxp, YOU_WIN, &game.you_win.width, &game.you_win.height);
	game.you_win.img = mlx_get_data_addr(game.you_win.img_p, &game.you_win.bpp, &game.you_win.s_line, &game.you_win.endian);
	//Display map for debug
	printf("\nTRIMMED LAYOUT:\n");
	while (game.map[i] != NULL)
	{
		printf("%d:%s\n", i, game.map[i]);
		i++;
	}
	game.player.vect = init_dir(game.map, game.player.pos);
	change_map(&game, (int)game.player.pos.x, (int)game.player.pos.y, '0');
	ft_start_display(game);
	return(0);
}
