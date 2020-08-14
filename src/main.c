/* *************cccd ************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 00:41:42 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/15 00:04:32 by yotillar         ###   ########.fr       */
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

t_graph	parser(char ***map)
{
	int	i;
	int	j;
	int	k;
	t_graph graph;

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
				find_info(map[0][i], &graph);
				k++;
				break;
			}
			j++;
		}
		i++;

	}
	find_map(map, i); 
	printf("ResX = %d, ResY = %d\n", graph.res[0], graph.res[1]);
	printf("Floor : R = %d, G = %d, B = %d\n", (int)graph.F[0],(int)graph.F[1], (int)graph.F[2]);	
	printf("Ceiling : R = %d, G = %d, B = %d\n", (int)graph.C[0],(int)graph.C[1], (int)graph.C[2]);

	/* verification de t_graph, renvoi d'erreur ? */
	return (graph);
}

int	main(int argc, char **argv)
{
	int	fd;
	t_graph	graph;
	char	**map;
	int	i;

	i = 0;
	if(argc ==  2)
	{
		fd = open(argv[1], O_RDONLY);
		printf("[START PARSING...]\n\n");
		map = get_line(fd);	
		close(fd);	
		graph = parser(&map);
		graph.pos = find_char(map);
		printf("\n[PARSING END!!!]\n");

		//Display map for debug
		printf("\nMap:\n");
		while (map[i] != NULL)
		{
			printf("%s\n", map[i]);
			i++;
		}


		ft_start_display(init_dir(map, graph.pos), graph, map);
	}
	return(0);
}
