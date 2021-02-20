/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pythagore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine </var/spool/mail/antoine>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 05:32:50 by antoine           #+#    #+#             */
/*   Updated: 2021/02/20 06:31:04 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

float	ft_pythagore(float x, float y)
{
	float sqr;
	float dist;

	sqr = (x * x)  + (y * y);
	dist = sqrtf(sqr);
	return (dist);
}
