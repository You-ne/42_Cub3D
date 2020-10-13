/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:12:48 by yotillar          #+#    #+#             */
/*   Updated: 2020/10/13 20:19:16 by yotillar         ###   ########.fr       */
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
# include <limits.h>
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

typedef struct s_img
{
	void	*img_p;
	char	*img;
	char	*path;

	int		endian;
	int		s_line;
	int		bpp;

	int		*width;
	int		*length;
}		t_img;

typedef struct s_player
{
	t_coor pos;
	t_coor vect;
}		t_player;

typedef struct s_game
{
	int	res[2]; // resolution X * Y

	int	F[3]; // RGB colors
	int	C[3];
	
	int	Fl; // Int colors
	int	Ce;

	char	**map;
	
	t_win	win;
	t_player player;

	t_img	NO; //Textures and Sprite
	t_img	SO;
	t_img	WE;
	t_img	EA;
	t_img	SP;
}		t_game;

/*
**------------------------------- Define ---------------------------------------
*/

//Parameters
# define FOV		70
# define CUB_SIZE	64
# define ROT_SPEED	1
# define FRONT_SPEED	0.15
# define BACK_SPEED	0.07
# define STRAFE_SPEED	0.10

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
# define ENTER	0xff
# define PAGE_UP 0xff55
# define PAGE_DOWN 0xff56
# define SHIFT_R 0xffe2
# define A	0x0041
# define D	0x0044
# define E	0x0045
# define Q	0x0051
# define S	0x0053
# define Z	0x005a

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

void	find_info(char *info, t_game *game);
void	find_map(char ***map, int line);
t_coor	find_char(char **map);
t_coor	init_dir(char **map, t_coor coor);

int	keyboard(int key, t_game *game);
int	ft_exit(t_win *win);

char	*ft_ctostr(int size, char c);
char	*ft_strmcat(char *str1, char *str2);
char	*ft_strdup(const char *str);
char	*extract_texture(t_game *game, char *str, char *img);
char	*ft_resize_col_texture(t_img texture, int height, int ncol);
void	ft_start_display(t_game);
void	ft_raymachine(t_game game);
void	ft_drawcol(int x, char *col, t_game game, t_img *img);


#endif
