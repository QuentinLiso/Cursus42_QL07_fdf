/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_Set_meshes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:38 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:07:40 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_vertices(t_map *map)
{
	map->vertices = map->height * map->width;
	map->raw_mesh = ft_calloc(map->vertices, sizeof(t_vector3));
	if (!map->raw_mesh)
		log_err("Set 3D mesh Malloc failed!");
	map->iso_mesh = ft_calloc(map->vertices, sizeof(t_vector3));
	if (!map->iso_mesh)
	{
		free(map->raw_mesh);
		log_err("Set 2D mesh Malloc failed!");
	}
}

void	set_3d_raw_mesh(t_map *map, int zoom)
{
	unsigned int		i;

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
			set_vertex_color(&map->raw_mesh[i]);
			i++;
			map->w_index++;
		}
		free(map->sizes[map->h_index]);
		map->h_index++;
	}
	free(map->sizes);
}

void	set_vertex_color(t_vector3 *vertex)
{
	if (vertex->z < SEA_LEVEL)
	{
		vertex->color = GRAY_COLOR;
		vertex->level = GRAY;
	}
	else if (vertex->z == SEA_LEVEL)
	{
		vertex->color = SEA_COLOR;
		vertex->level = SEA;
	}
	else if (vertex->z <= GROUND_LEVEL)
	{
		vertex->color = GROUND_COLOR;
		vertex->level = GROUND;
	}
	else if (vertex->z <= MOUNTAIN_LEVEL)
	{
		vertex->color = MOUNTAIN_COLOR;
		vertex->level = MOUNTAIN;
	}
	else
	{
		vertex->color = SNOW_COLOR;
		vertex->level = SNOW;
	}
}

void	set_3d_iso_mesh(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->iso_mesh[i].x = map->raw_mesh[i].x;
		map->iso_mesh[i].y = map->raw_mesh[i].y;
		map->iso_mesh[i].z = map->raw_mesh[i].z;
		map->iso_mesh[i].color = map->raw_mesh[i].color;
		map->iso_mesh[i].level = map->raw_mesh[i].level;
		i++;
	}
}

void	centering_mesh(t_map *map)
{
	set_3d_iso_mesh(map);
	map->translation.x = 0;
	map->translation.y = 0;
}
