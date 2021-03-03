/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:29:04 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 20:09:18 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_res(t_game *game)
{
	int		wmax;
	int		hmax;

	mlx_get_screen_size(game->win.mlxp, &wmax, &hmax);
	if (game->res[0] > wmax)
		game->res[0] = wmax;
	if (game->res[1] > hmax)
		game->res[1] = hmax;
}

void	check_args(t_game *game, char **argv, int argc)
{
	game->is_bmp = 0;
	if (argc < 1)
		ft_error("No argument !!\n", game);
	if (argc == 1)
		ft_error("No map linked !!\n", game);
	if (argc == 3 && (ft_strcmp(argv[2], "--save") != 0))
		ft_error("Incorrect argument for saving !!\n", game);
	else if (argc == 3)
		game->is_bmp = 1;
	if (argc > 3)
		ft_error("Too much arguments for Cub3D !!\n", game);
}

void	check_fd(t_game *game, char *argv)
{
	int		fd;
	int		ret;
	char	buffer[1];
	char	*ext;

	fd = open(argv, O_RDONLY);
	if (fd == 0 || (ret = read(fd, buffer, 1)) < 0)
		ft_error("Map file not found, please verify path! \n", game);
	if ((ext = ft_strrchr(argv, '.')) != NULL)
	{
		if (ft_strlen(ext) == 4)
		{
			if (ft_strncmp(ext, ".cub", 4) != 0)
				ft_error("Wrong file extension for map ! \n", game);
			return ;
		}
		ft_error("Wrong file extension for map ! \n", game);
	}
	else
		ft_error("Wrong file extension for map ! \n", game);
}

void	checkpath(char *path, t_game *game)
{
	int		fd;
	int		ret;
	char	buffer[1];
	char	*ext;

	fd = open(path, O_RDONLY);
	if (fd == 0 || (ret = read(fd, buffer, 1)) < 0)
		ft_error("Cannot read texture, please verify path! \n", game);
	if ((ext = ft_strrchr(path + 1, '.')) != NULL)
	{
		if (ft_strlen(ext) == 4)
		{
			if (ft_strncmp(ext, ".xpm", 4) != 0)
				ft_error("Wrong file extension for texture ! \n", game);
			return ;
		}
		ft_error("Wrong file extension for texture ! \n", game);
	}
	else
		ft_error("Wrong file extension for texture ! \n", game);
}

void	check_settings(t_game *game)
{
	if (game->found[2] == 0 || game->found[3] == 0 || game->found[4] == 0 ||
	game->found[5] == 0)
		ft_error("Missing a wall texture!\n", game);
	if (game->found[0] == 0 || game->found[1] == 0)
		ft_error("Missing Floor Or Ceiling Color!\n", game);
}
