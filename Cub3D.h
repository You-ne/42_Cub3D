/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:12:48 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/13 02:06:19 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**------------------------------- Headers --------------------------------------
*/

# include <time.h>
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
	t_coor	pos;
	t_coor	vect;

	float	pv;
	t_img	*weapon;
	int		fire;
}		t_player;

typedef struct s_bmp
{
	int						zero;
	unsigned int			size;
	unsigned int			offset;
	int						dib_size;
	int						width;
	int						heigth;
	unsigned short int		planes;
	unsigned short int		bpp;
}		t_bmp;

typedef struct s_enemy
{
	int x;
	int y;
	int tir;
	int pv;
	int damage;
	char chr;
	clock_t tdeath;
	struct s_enemy *next;
}		t_enemy;

typedef struct s_game
{
	int			is_bmp;
	t_bmp		bmp;

	int			res[2]; // resolution X * Y

	int			F[3]; // RGB colors
	int			C[3];
	
	int			Fl; // Int colors
	int			Ce;

	int			up;
	int			down;
	int			left;
	int			rot_left;
	int			right;
	int			rot_right;
	int			sprint;
	int			tilt;

	int			fire;
	clock_t		fire_t1;

	char		**map;

	int			enemy_fire;
	clock_t		enemy_fire_t1;
	t_enemy		enemies;

	t_win		win;
	t_player	player;

	t_img		SKY;
	t_img		NO; //Textures and Sprite
	t_img		SO;
	t_img		WE;
	t_img		EA;
	t_img		SP;
	t_img		SA;
}		t_game;

/*
**------------------------------- Define ---------------------------------------
*/

//Parameters
# define LINUX		1
# define FOV		60
//# define CUB_SIZE	64
# define NB_PARAMS	8 + 10

# define ROT_SPEED		0.07
# define ZROT_SPEED		2
# define FRONT_SPEED	0.15
# define BACK_SPEED		0.07
# define STRAFE_SPEED	0.07
# define SPRINT_SPEED	0.22

# define W1 "./sprites/M2GFB0.xpm"
# define W2 "./sprites/M2GFA0.xpm"
# define W3 "./sprites/M2GFC0.xpm"
/*
# define E1 "./sprites/enemy_aim.xpm"
# define E2 "./sprites/enemy_shoot.xpm"
*/
# define D1 "./sprites/doors_close.xpm"
# define D2 "./sprites/doors_open.xpm"

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
# define X			0x78
# define TC			0x63
# define T			0x74
# define SPACE		0x20

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
void	check_args(t_game *game, char **argv, int argc);
void	check_fd(t_game *game, char *argv);

void	find_info(char *info, t_game *game);
void	get_res(char *info, t_game *game);
void	find_map(t_game *game, int line);
t_coor	find_char(char **map);
t_coor	init_dir(char **map, t_coor coor);
t_img	find_sprite(t_game *game, char chr);

void	draw_sky(t_game *game, t_img *img);
void	draw_life(t_game *game, t_img *img);
void	draw_weapon(t_game *game, t_img *img, t_img *tex);
t_img	*weapon_fire_animation(t_game *game, t_img *);
void	weapon_fire(t_game *game, t_coor *tir);

void	sp_events(t_game *game);
double	sp_size(char chr);
int		sp_collision(int x, int y, char **map);
void	teleportation(t_player *player, double x, double y);
void	change_map(t_game *game, int x, int y, char chr);
void	change_pv(t_player *player, float pv);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	apply_mvmt(t_game *game);

void	ft_error(const char *str, t_game *game);
int		ft_exit(int keycode, t_game *game);
void	save(t_game *game, t_img *img);

char	*ft_ctostr(int size, char c);
char	*ft_strmcat(char *str1, char *str2);
char	*ft_strdup(const char *str);
int		is_str_charset(char *charset, char *str);
int		in_str(char c, char *str);

void	extract_texture(t_game *game, char *str, char *img, char chr);
void	extract_anim(t_game *game, char *str, char chr);
void	extract_file(char *path, t_game *game);
char	*ft_resize_col_texture(t_img texture, int height, int ncol);
void	ft_start_display(t_game);
void	ft_raymachine(t_game *game);
t_coor	ft_raycannon(t_coor pos, t_coor vect, double angle, t_game *game);
void	ft_drawcol(t_coor *heightncol, t_img texture, t_game *game, t_img *img);

#endif
