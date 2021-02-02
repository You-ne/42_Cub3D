/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:12:48 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/03 00:07:49 by yotillar         ###   ########.fr       */
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
# include "./src/Gnl/get_next_line.h"
# include "./src/Libft/libft.h"

/*
**------------------------------- Structures -----------------------------------
*/

typedef struct s_coor
{
	double			x;
	double			y;
	double			dist;
	struct s_coor	*next;
}		t_coor;

typedef struct s_window
{
	void	*mlxp;
	void	*winp;
}		t_win;

typedef struct s_img
{
	void			*img_p;
	char			*img;
	char			*path;

	int				endian;
	int				s_line;
	int				bpp;

	int				width;
	int				height;

	char			chr;
	struct s_img	*next;
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

	int	up;
	int	down;
	int	left;
	int	rot_left;
	int	right;
	int	rot_right;
	int	sprint;

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
# define LINUX		1
# define FOV		60
# define CUB_SIZE	64
# define ROT_SPEED	0.01
# define FRONT_SPEED	0.15
# define BACK_SPEED		0.07
# define STRAFE_SPEED	0.10
# define SP2_SIZE		0.30
# define SP3_SIZE		1.20
# define SP4_SIZE		1.00
# define SP5_SIZE		0.70

//Colors
# define GREEN	"\e[0;92m"
# define RED	"\e[0;91m"
# define RESET	"\033[0m"

//KEY CODES

# define LEFT		65361
# define UP			65362
# define RIGHT		65363
# define DOWN		65364
# define ESC		65307
# define SHIFT_R	0xffe2
# define Z			119 /* but its W */
# define A			97
# define S			115
# define D			100
# define Q			113
# define E			101

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
void	get_res(char *info, t_game *game);
void	find_map(char ***map, int line);
t_coor	find_char(char **map);
t_coor	init_dir(char **map, t_coor coor);
t_img	find_sprite(t_game *game, char chr);
double	find_size_sp(char chr);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	apply_mvmt(t_game *game);
int		ft_exit(t_win *win);

char	*ft_ctostr(int size, char c);
char	*ft_strmcat(char *str1, char *str2);
char	*ft_strdup(const char *str);
void	extract_texture(t_game *game, char *str, char *img, char chr);
char	**extract_map(int fd);
char	*ft_resize_col_texture(t_img texture, int height, int ncol);
void	ft_start_display(t_game);
void	ft_raymachine(t_game *game);
void	ft_drawcol(t_coor *heightncol, t_img texture, t_game *game, t_img *img);


#endif
