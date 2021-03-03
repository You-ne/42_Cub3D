/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 04:12:48 by yotillar          #+#    #+#             */
/*   Updated: 2021/03/03 05:10:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**------------------------------- Headers --------------------------------------
*/

# include <time.h>
# include <mlx.h>
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

typedef struct	s_coor
{
	float			x;
	float			y;
	float			dist;
	int				coor_sp;
	struct s_coor	*next;
}				t_coor;

typedef struct	s_window
{
	void	*mlxp;
	void	*winp;
}				t_win;

typedef struct	s_img
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
}				t_img;

typedef struct	s_player
{
	t_coor	pos;
	t_coor	vect;

	float	pv;
	t_img	*weapon;
	t_img	*weapon2;
	int		num_weapon;
	int		fire;
	int		damage;
	int		ammo;
}				t_player;

typedef struct	s_bmp
{
	int						zero;
	unsigned int			size;
	unsigned int			offset;
	int						dib_size;
	int						width;
	int						heigth;
	unsigned short int		planes;
	unsigned short int		bpp;
}				t_bmp;

typedef struct	s_enemy
{
	int				x;
	int				y;
	int				fire;
	int				pv;
	int				damage;
	char			chr;
	int				time_anim;
	clock_t			tdeath;
	clock_t			tseen;
	struct s_enemy	*next;
}				t_enemy;

typedef struct	s_game
{
	int			is_bmp;
	t_bmp		bmp;

	int			res[2];

	int			f[3];
	int			c[3];

	int			fl;
	int			ce;

	int			found[8];
	int			map_found;
	int			start_found;

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

	t_coor		secret;

	t_enemy		*enemies;

	int			win_created;
	t_win		win;
	t_player	player;

	clock_t		end;

	t_img		game_over;
	t_img		you_win;
	t_img		sky;
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_img		*sp;
	t_img		*sa;
}				t_game;

/*
**------------------------------- Define ---------------------------------------
*/

//Parameters
# define FOV		60

# define ROT_SPEED		0.07
# define ZROT_SPEED		2
# define FRONT_SPEED	0.13
# define BACK_SPEED		0.07
# define STRAFE_SPEED	0.07
# define SPRINT_SPEED	0.23

# define M1 "./cont/guns/M2GFB0.xpm"
# define M2 "./cont/guns/M2GFA0.xpm"
# define M3 "./cont/guns/M2GFC0.xpm"

# define P1 "./cont/guns/gunA.xpm"
# define P2 "./cont/guns/gunB.xpm"
# define P3 "./cont/guns/gunD.xpm"

# define GAME_OVER "./cont/GameOver.xpm"
# define YOU_WIN "./cont/YOUWIN.xpm"

# define T_AIM_ANIM 20
# define T_DEATH_ANIM 15

# define AMMO_MAX 30

//KEY CODES

# define LEFT		65361
# define UP			65362
# define RIGHT		65363
# define DOWN		65364
# define ESC		65307
# define SHIFT_R	0xffe2
# define Z			0x7a
# define A			0x61
# define S			0x73
# define D			100
# define Q			113
# define E			0x65
# define X			0x78
# define TC			0x63
# define T			0x74
# define SPACE		0x20

//EVENTS
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5

/*
**------------------------------- Prototypes -----------------------------------
*/

void	extract_xpm(t_game *game, t_img *tex, char *str);
void	my_delay(int i);
void	end_screen(t_game *game, t_img *tex, t_img *img);
void	init_keys(t_game *game);
void	check_args(t_game *game, char **argv, int argc);
void	check_fd(t_game *game, char *argv);
void	checkpath(char *path, t_game *game);
void	check_res(t_game *game);
void	check_settings(t_game *game);

void	find_info(char *info, t_game *game);
void	get_res(char *info, t_game *game);
int		get_color(char *info, t_game *game, char param);
int		find_map(t_game *game, int line);
void	verify_map(t_game *game, char *sp_set);
t_coor	find_start(t_game *game);
t_img	*find_sprite(t_game *game, char chr);
char	*count_sprites(t_game *game, int time, char *sp_set);
void	param_enemy(t_enemy *enemy, char chr);
void	find_secret_door(t_game *game);
t_coor	*ft_add_door(t_game *game, t_coor *ray, t_coor *dir, t_coor *eqline);

t_coor	init_dir(char **map, t_coor coor);
void	init(t_game *game);
void	init_screens(t_game *game);

void	ft_xray(t_coor *eqline, t_coor dir, t_coor *ray, t_game *game);
void	ft_yray(t_coor *eqline, t_coor dir, t_coor *ray, t_game *game);
void	ft_vertical_ray(t_coor *eqline, t_coor *dir, t_coor *ray, t_game *game);

void	draw_sky(t_game *game, t_img *img);
void	draw_life(t_game *game, t_img *img);
void	draw_weapon(t_game *game, t_img *img, t_img *tex);
t_img	*weapon_fire_animation(t_game *game, t_img *);
void	weapon_fire(t_game *game, t_coor *tir);

t_img	*find_animation(t_game *game, int info, t_img *tex, char chr);
t_img	*enemy_fire_animation(t_game *game, t_img *tex, t_enemy *enemy);
t_img	*death_animation(t_game *game, t_img *tex, t_enemy *enemy);
t_img	*aim_animation(t_game *game, t_img *tex, t_enemy *enemy);
t_img	*weapon_fire_animation(t_game *game, t_img *weapon);
char	find_shooting_chr(char chr);
int		is_alive_or_dead(char chr);

void	sp_events(t_game *game);
float	sp_size(char chr);
int		sp_collision(int x, int y, char **map);
void	teleportation(t_player *player, float x, float y);
void	change_map(t_game *game, int x, int y, char chr);
void	change_pv(t_game *game, float pv);
void	change_enemy_pv(t_game *game, t_enemy* enemy, int pv);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	apply_mvmt(t_game *game);
void	rotation(t_coor *vect, float angle);
void	open_door(t_game *game);

void	ft_error(const char *str, t_game *game);
int		ft_exit(int keycode, t_game *game);
void	save(t_game *game, t_img *img);

char	*ft_ctostr(int size, char c);
char	*ft_strmcat(char *str1, char *str2);
char	*ft_strdup(const char *str);
int		is_str_charset(char *charset, char *str);
int		in_str(char c, char *str);

int		count_animation_sprites(t_img *tex);
char	find_death_chr(char chr);
t_enemy	*find_enemy(t_game *game, int x, int y, char chr);
void	change_enemy_pv(t_game *game, t_enemy *enemy, int pv);
t_coor	ft_dirsteps(t_coor vecray);

char	ft_ray_collision(char **map, t_coor *ray, t_coor *dir);

float	ft_pythagore(float x, float y);

t_coor	*ft_add_sprite(t_game *game, t_coor *ray, t_coor *dir, t_coor *eqline);

void	extract_file(char *path, t_game *game);
t_img	*get_weapon_tex(t_game *game, char *n1, char *n2, char *n3);
void	extract_texture(t_game *game, char *str, char *img, char chr);
int		save_texture(char *info, t_game *game, char param);
void	no_we_textures(t_game *game, char param, char *str);
void	so_ea_textures(t_game *game, char param, char *str);
void	sky_texture(t_game *game, char param, char *str);
void	extract_sprite(t_game *game, char *str, char chr, t_img *sp_sa);
int		save_sprite(char *info, t_game *game, char chr, char mode);

void	ft_start_display(t_game *game);

void	ft_raymachine(t_game *game, t_img *img);
t_coor	*ft_raycannon(t_coor *pos, t_coor *vect, float angle, t_game *game);
void	ft_drawcol(t_coor *heightncol, t_img *texture, t_game *gam, t_img *img);
void	free_ray(t_coor *ray);
void	ft_projection(t_game *game, t_coor *ray, int x, t_img *img);
void	ft_texture_put(t_img *img, int x, int y, char *texture);
void	ft_texture_put_sp(t_img *img, t_coor xy, char *texture, int i);
void	ft_pixel_put(t_img *img, int x, int y, int color);
#endif
