#include "fdf.h"

void	set_vertices(t_map *map)
{
	map->vertices = map->height * map->width;
	map->raw_mesh = ft_calloc(map->vertices, sizeof(t_vector3));
	if (!map->raw_mesh)
		log_err("Set 3D mesh Malloc failed!");
	map->iso_mesh = ft_calloc(map->vertices, sizeof(t_vector2));
	if (!map->iso_mesh)
	{
		free(map->raw_mesh);
		log_err("Set 2D mesh Malloc failed!");
	}
}

void	set_3d_raw_mesh(t_map *map, int zoom)
{
	unsigned int		i;

	set_vertices(map);
	i = 0;
	map->h_index = 0;
	while (map->h_index < map->height)
	{
		map->w_index = 0;
		while (map->w_index < map->width)
		{
			map->raw_mesh[i].x = map->w_index * zoom;
			map->raw_mesh[i].y = map->h_index * zoom;
			map->raw_mesh[i].z = map->sizes[map->h_index][map->w_index];
			i++;
			map->w_index++;
		}
		free(map->sizes[map->h_index]);
		map->h_index++;
	}
	free(map->sizes);
}

void	set_2d_iso_mesh(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->iso_mesh[i].x = cos_deg(30.0f) * map->raw_mesh[i].x
			- cos_deg(30.0f) * map->raw_mesh[i].y;
		map->iso_mesh[i].y = sin_deg(30.0f) * map->raw_mesh[i].x
			+ sin_deg(30.0f) * map->raw_mesh[i].y - map->raw_mesh[i].z;
		map->iso_mesh[i].x += map->translation.x + WINDOW_WIDTH / 2;
		map->iso_mesh[i].y += map->translation.y + WINDOW_HEIGHT / 2;
		i++;
	}
}

void	set_2d_front_mesh(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->iso_mesh[i].x = map->raw_mesh[i].x;
		map->iso_mesh[i].y = -map->raw_mesh[i].z;
		map->iso_mesh[i].x += map->translation.x + WINDOW_WIDTH / 2;
		map->iso_mesh[i].y += map->translation.y + WINDOW_HEIGHT / 2;
		i++;
	}
}

void	centering_mesh(t_map *map)
{
	map->translation.x = 0.0f;
	map->translation.y = 0.0f;
}
