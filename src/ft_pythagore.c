#include "../cub3d.h"

float		ft_pythagore(float x, float y)
{
	float	sqr;
	float	dist;

	sqr = (x * x) + (y * y);
	dist = sqrtf(sqr);
	return (dist);
}
