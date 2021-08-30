#include "../cub3d.h"

void	ft_clean_game(t_game *game)
{
	if (game->is_bmp == 0 && game->win_created == 1)
		mlx_destroy_window(game->win.mlxp, game->win.winp);
}

int		ft_exit(int keycode, t_game *game)
{
	int	rien;

	rien = keycode * 0;
	if (game)
		ft_clean_game(game);
	exit(0);
	return (rien);
}

void	ft_error(char *str, t_game *game)
{
	ft_putstr_fd(str, 2);
	ft_exit(65307, game);
}
