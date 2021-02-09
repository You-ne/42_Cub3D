/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:29:04 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/05 08:14:37 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	check_args(t_game *game, char **argv, int argc)
{
	game->bmp = 0;
	if (argc < 1)
		ft_error("No argument !!\n", game);
	if (argc == 1)
		ft_error("No map linked !!\n", game);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 50) != 0)) // maybe use strcmp
		ft_error("Incorrect argument for saving !!\n", game);
	else if (argc == 3)
		game->bmp = 1;
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
			return;
		}
			ft_error("Wrong file extension for map ! \n", game);
	}
	else
			ft_error("Wrong file extension for map ! \n", game);
}
