/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/16 01:32:49 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"
#include "../Gnl/get_next_line.h"

char	**get_line(int fd)
{
	int	i;
	char	*tmp;
	char	**map;

	i = 0;
	/* gérer taille */
	if(!(map = (char**)malloc(sizeof(char*) * 50)))
		return (NULL);
	while(get_next_line(fd, &tmp) > 0)
	{
		map[i] = ft_strdup(tmp);
		i++;
	}
	map[i] = NULL;
	return(map);
}

t_game	parser(char ***map)
{
	int	i;
	int	j;
	int	k;
	t_game game;

	k = 0;
	i = 0;
	while(map[0][i] != NULL && k < 3)
	{
		j = 0;
		while(map[0][i][j] != '\0')
		{
			/* temporaire, rajouter détection mauvaises lignes */
			if (map[0][i][j] > 65 && map[0][i][j] < 91)
			{
				find_info(map[0][i], &game);
				k++;
				break;
			}
			j++;
		}
		i++;

	}
	find_map(map, i); 
	printf("ResX = %d, ResY = %d\n", game.res[0], game.res[1]);
	printf("Floor : R = %d, G = %d, B = %d\n", (int)game.F[0],(int)game.F[1], (int)game.F[2]);	
	printf("Ceiling : R = %d, G = %d, B = %d\n", (int)game.C[0],(int)game.C[1], (int)game.C[2]);

	/* verification de t_game, renvoi d'erreur ? */
	return (game);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_game	game;
	char	**map;
	int	i;

	i = 0;
	if(argc ==  2)
	{
		fd = open(argv[1], O_RDONLY);
		printf("[START PARSING...]\n\n");
		map = get_line(fd);	
		close(fd);	
		game = parser(&map);
		game.player.pos = find_char(map);
		printf("\n[PARSING END!!!]\n");

		//Display map for debug
		printf("\nMap:\n");
		while (map[i] != NULL)
		{
			printf("%s\n", map[i]);
			i++;
		}

		game.player.vect = init_dir(map, game.player.pos);
		ft_start_display(game, map);
	}
	return(0);
}
