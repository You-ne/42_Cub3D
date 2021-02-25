/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:43:48 by antoine           #+#    #+#             */
/*   Updated: 2021/02/25 04:57:59 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

t_img aim_animation(t_game *game, t_img *tex, t_enemy *enemy)
{
	clock_t t2;
	int		centisec;
	int i;
	int n;

	if ((long)enemy->tseen <= 0)
		enemy->tseen = clock();
	t2 = clock();
	n = count_animation_sprites(tex);
	i = 1;
	centisec = (int)roundf((float)((long)t2 - (long)enemy->tseen) / CLOCKS_PER_SEC * 100);
	while (centisec % (n * 100) > 100 * i && i < n)
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

	if ((long)enemy->tseen <= 0)
		enemy->tseen = clock();
	t2 = clock();
	centisec = (int)roundf((float)((long)t2 - (long)enemy->tseen) / CLOCKS_PER_SEC * 100);
	//	printf("centisec=%i, fire_t1=%i\n", centisec, game->fire_t1);
	if (centisec % enemy->time_anim < 14)
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
	centisec = (int)roundf((float)((long)t2 - (long)enemy->tdeath) / CLOCKS_PER_SEC * 100);
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


void	do_fire(t_game *game)
{
	t_coor *tir;

	if (game->player.fire == 0)
	{
		if (game->player.ammo != 0)
		{
			tir =
			ft_raycannon(&game->player.pos, &game->player.vect, 0.0, game);
			system("aplay -N -q ./cont/sounds/gun_shot.wav &");
			weapon_fire(game, tir);
			game->player.ammo -= 1;
			free_ray(tir);
		}
		else
			system("aplay -N -q ./cont/sounds/gun_change.wav &");
	}
	game->player.fire = 1;
}


t_img	*weapon_fire_animation(t_game *game, t_img *weapon)
{
	t_img	*tmp;
	clock_t	t2;
	int	centisec;
	int	time_anim;

	if (game->player.num_weapon == 1)
		time_anim = 66;
	else if (game->player.num_weapon == 2)
		time_anim = 33;
	tmp = (game->player.ammo == 0 ? weapon->next->next : weapon);
	if (game->fire == 1)
	{
		t2 = clock();
		centisec = ((float)(t2 - game->fire_t1) / CLOCKS_PER_SEC) * 100;
		if ((int)centisec % time_anim < 11)
		{
			do_fire(game);
			tmp = (game->player.ammo == 0 ? tmp : weapon->next);
		}
		else
			game->player.fire = 0;
		if ((int)centisec % time_anim >= 11 && (int)centisec % time_anim < 22)
			tmp = (game->player.ammo == 0 ? tmp : weapon->next->next);
	}
	return (tmp);
}
/*
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
*/
