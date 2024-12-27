#include "fdf.h"

void	zoom_in(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->raw_mesh[i].x *= map->zoom_coeff;
		map->raw_mesh[i].y *= map->zoom_coeff;
		map->raw_mesh[i].z *= map->zoom_coeff;
		i++;
	}
}

void	zoom_out(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->raw_mesh[i].x /= map->zoom_coeff;
		map->raw_mesh[i].y /= map->zoom_coeff;
		map->raw_mesh[i].z /= map->zoom_coeff;
		i++;
	}
}
