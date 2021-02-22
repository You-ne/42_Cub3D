/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:43:48 by antoine           #+#    #+#             */
/*   Updated: 2021/02/22 05:34:08 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_img aim_animation(t_game *game, t_img *tex, t_enemy *enemy)
{
	clock_t t2;
	int		centisec;
	int i;
	int n;

	if (!enemy->tseen)
		enemy->tseen = clock();
	t2 = clock();
	n = count_animation_sprites(tex);
	i = 1;
	centisec = (int)roundf((float)(t2 - enemy->tseen) / CLOCKS_PER_SEC * 100);
	while (centisec % (n * 15) > 15 * i && i < n)
	{
		tex = tex->next;
		i++;
	}
	if (i == n)
	{
		change_map(game, enemy->x, enemy->y, find_shooting_chr(tex->chr));
	}
	return (*tex);
}

t_img enemy_fire_animation(t_game *game, t_img *tex, t_enemy *enemy)
{
	clock_t	t2;
	int		centisec;

	t2 = clock();
	centisec = (int)roundf((float)(t2) / CLOCKS_PER_SEC * 100);
//	printf("centisec=%i, fire_t1=%i\n", centisec, game->fire_t1);
	if (centisec % enemy->time_anim < 10)
	{
		if (enemy->fire == 0)
		{
			system("aplay -N -q ./sprites/gun_shot.wav &");
			change_pv(&game->player, enemy->damage);
		}
		enemy->fire = 1;
		return (*(tex->next));
	}
	else
		enemy->fire = 0;
	return (*tex);
	}

t_img death_animation(t_game *game, t_img *tex, t_enemy *enemy)
{
	clock_t t2;
	int		centisec;
	int i;
	int n;

	t2 = clock();
	n = count_animation_sprites(tex);
	i = 1;
	centisec = (int)roundf((float)(t2 - enemy->tdeath) / CLOCKS_PER_SEC * 100);
	while (centisec % (n * 15) > 15 * i && i < n)
	{
		tex = tex->next;
		i++;
	}
	if (i == n)
	{
		change_map(game, enemy->x, enemy->y, find_death_chr(tex->chr));
	}
	return (*tex);
}

t_img	*weapon_fire_animation(t_game *game, t_img *weapon)
{
	clock_t	t2;
	int	centisec;
	t_coor tir;

	if (game->fire == 1)
	{
		t2 = clock();
		centisec = ((float)(t2 - game->fire_t1) / CLOCKS_PER_SEC) * 100;
		if ((int)centisec % 33 < 11)
		{
			tir = ft_raycannon(game->player.pos, game->player.vect, 0.0, game);
			if (game->player.fire == 0)
			{
				system("aplay -N -q ./sprites/gun_shot.wav &");
				weapon_fire(game, &tir);
			}
			game->player.fire = 1;
			return (weapon->next);
		}
		else
			game->player.fire = 0;
		if ((int)centisec % 33 >= 11 && (int)centisec % 33 < 22)
			return (weapon->next->next);
	}
	return (weapon);
}

t_img perpetual_animation(t_game *game, t_img *tex)
{
	clock_t t2;
	int		centisec;
	int n;
	int i;

	n = count_animation_sprites(tex);
	t2 = clock();
	i = 1;
	centisec = (int)roundf((float)(t2) / CLOCKS_PER_SEC * 100);
	while (centisec % (n * 15) > 15 * i && i < n)
	{
		tex = tex->next;
		i++;
	}
	return (*tex);
}
