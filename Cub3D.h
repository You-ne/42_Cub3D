/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:12:48 by yotillar          #+#    #+#             */
/*   Updated: 2020/08/15 01:48:34 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**------------------------------- Headers --------------------------------------
*/

# include <mlx.h>
//# include "./minilibx/mlx_int.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "./Gnl/get_next_line.h"
# include "./Libft/libft.h"

/*
**------------------------------- Structures -----------------------------------
*/

typedef struct s_coor
{
	double	x;
	double	y;
	double	dist;
}		t_coor;

typedef struct s_window
{
	void	*mlxp;
	void	*winp;
}		t_win;

typedef struct s_graph
{
	int	res[2];
	int	F[3];
	int	C[3];
	t_win	win;
	t_coor	pos;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
}		t_graph;

/*
**------------------------------- Define ---------------------------------------
*/

//Parameters
# define FOV	120
# define CUB_SIZE	64


//Colors
# define GREEN	"\e[0;92m"
# define RED	"\e[0;91m"
# define RESET	"\033[0m"

//KEY CODES

# define LEFT	0xff51
# define UP	0xff52
# define RIGHT	0xff53
# define DOWN	0xff54
# define ESC	0xFF1b
# define SPACE	0x7780
# define TAB	0xff89
# define ENTER	0xff8d

//EVENTS
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5

# define KEY_PRESS_M 1L << 0
# define KEY_RELEASE_M 1L << 1
# define BUTTON_PRESS_M 1L << 2
# define BUTTON_RELEASE_M 1L << 3
/*
**------------------------------- Prototypes -----------------------------------
*/

void	find_info(char *info, t_graph *graph);
void	find_map(char ***map, int line);
t_coor	find_char(char **map);
t_coor	init_dir(char **map, t_coor coor);

char	*extract_path(char *dest, char *src);
void	ft_start_display(t_coor vect, t_graph, char **map);
void	ft_raymachine(t_coor vect, t_graph graph, char **map);


#endif
