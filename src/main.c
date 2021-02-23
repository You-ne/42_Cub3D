/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/23 20:06:52 by antoine          ###   ########.fr       */
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


int			parser(t_game *game) //too long
{
	int	i;
	int	j;

	i = 0;
	while(game->map[i] != NULL)
	{
		j = 0;
		while(game->map[i][j] != '\0')
		{
			if (game->map[i][j] == '1')
				return(find_map(game, i, game->nb_params));
			if (game->map[i][j] > 65 && game->map[i][j] < 91)
			{
				game->nb_params++;
				find_info(game->map[i], game);
				break;
			}
			else if (game->map[i][j] == ' ')
				j++;
			else
				ft_error("Invalid line in .cub file\n\n", game);
		}
		i++;
	}
	return (0);
}

t_img	*get_weapon_tex(t_game *game, char *n1, char *n2, char *n3)
{
	t_img *weapon;
	t_img *weapon2;
	t_img *weapon3;

	weapon = (struct s_img*)malloc(sizeof(struct s_img));
	weapon2 = (struct s_img*)malloc(sizeof(struct s_img));
	weapon3 = (struct s_img*)malloc(sizeof(struct s_img));

	weapon->img_p = mlx_xpm_file_to_image(game->win.mlxp, n1, &weapon->width, &weapon->height);
	weapon->img = mlx_get_data_addr(weapon->img_p, &weapon->bpp, &weapon->s_line, &weapon->endian);
	weapon2->img_p = mlx_xpm_file_to_image(game->win.mlxp, n2, &weapon2->width, &weapon2->height);
	weapon2->img = mlx_get_data_addr(weapon2->img_p, &weapon2->bpp, &weapon2->s_line, &weapon2->endian);
	weapon3->img_p = mlx_xpm_file_to_image(game->win.mlxp, n3, &weapon3->width, &weapon3->height);
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

void	init(t_game *game)
{
	game->Fl = 0;
	game->Ce = 0;
	game->map_found = 0;
	game->nb_params = 0;
	game->secret.x = 0;
	game->secret.y = 0;
	game->secret.dist = 0;
	game->SA.chr = '1';
	game->player.num_weapon = 1;
	game->player.damage = -40;
	game->player.pv = 100.0;
	game->tilt = 0;
	game->player.ammo = 30;
}

void	init_screens(t_game *game)
{
	game->game_over.img_p = mlx_xpm_file_to_image(game->win.mlxp, GAME_OVER, &game->game_over.width, &game->game_over.height);
	game->game_over.img = mlx_get_data_addr(game->game_over.img_p, &game->game_over.bpp, &game->game_over.s_line, &game->game_over.endian);
	game->you_win.img_p = mlx_xpm_file_to_image(game->win.mlxp, YOU_WIN, &game->you_win.width, &game->you_win.height);
	game->you_win.img = mlx_get_data_addr(game->you_win.img_p, &game->you_win.bpp, &game->you_win.s_line, &game->you_win.endian);
	game->player.vect = init_dir(game->map, game->player.pos);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;

	i = 0;
	init(&game);
	check_args(&game, argv, argc);
	check_fd(&game, argv[1]);
	extract_file(argv[1], &game);
	find_res(&game);
	game.win.mlxp = mlx_init();
	parser(&game);
	game.player.pos = find_char(&game);
	game.player.weapon = get_weapon_tex(&game, P1, P2, P3);
	game.player.weapon2 = get_weapon_tex(&game, M1, M2, M3);
	game.enemy_fire_t1 = clock();
	init_screens(&game);
	change_map(&game, (int)game.player.pos.x, (int)game.player.pos.y, '0');
	ft_start_display(game);
	return(0);
}
