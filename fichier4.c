#include "fdf.h"

void	set_3d_raw_mesh(t_scene *scene, int step)
{
	unsigned int		i;

	set_vertices(scene);
	scene->map->raw_mesh = ft_calloc(scene->map->height * scene->map->width, sizeof(t_vector3));
	if (!scene->map->raw_mesh)
		log_err("Set 3D mesh Malloc failed!");
	i = 0;
	scene->map->h_index = 0;
	while (scene->map->h_index < scene->map->height)
	{
		scene->map->w_index = 0;
		while (scene->map->w_index < scene->map->width)
		{
			scene->map->raw_mesh[i].x = scene->map->w_index * step;
			scene->map->raw_mesh[i].y = scene->map->h_index * step;
			scene->map->raw_mesh[i].z = scene->map->sizes[scene->map->h_index][scene->map->w_index];
			i++;
			scene->map->w_index++;
		}
		free(scene->map->sizes[scene->map->h_index]);
		scene->map->h_index++;
	}
	free(scene->map->sizes);
}

void	set_vertices(t_scene *scene)
{
	scene->map->vertices = scene->map->height * scene->map->width;
}

void	set_2d_iso_mesh(t_scene *scene)
{
	unsigned int	i;

	scene->map->iso_mesh = ft_calloc(scene->map->vertices, sizeof(t_vector2));
	if (!scene->map->iso_mesh)
	{
		free(scene->map->raw_mesh);
		log_err("Set 2D mesh Malloc failed!");
	}
	i = 0;
	while (i < scene->map->vertices)
	{
		scene->map->iso_mesh[i].x = cos_deg(30.0f) * scene->map->raw_mesh[i].x - cos_deg(30.0f) * scene->map->raw_mesh[i].y;
		scene->map->iso_mesh[i].y = sin_deg(30.0f) * scene->map->raw_mesh[i].x + sin_deg(30.0f) * scene->map->raw_mesh[i].y - scene->map->raw_mesh[i].z;
		i++;
	}
}

void	set_barycenter_mesh(t_scene *scene)
{
	unsigned int	i;
	t_vector2		barycenter;

	i = 0;
	barycenter = (t_vector2){0.0f, 0.0f};
	while (i < scene->map->vertices)
	{
		barycenter.x += scene->map->iso_mesh[i].x;
		barycenter.y += scene->map->iso_mesh[i].y;
		i++;
	}
	barycenter.x = barycenter.x / (double)i;
	barycenter.y = barycenter.y / (double)i;
	scene->map->center.x = barycenter.x;
	scene->map->center.y = barycenter.y;
}

void	centering_mesh(t_scene *scene)
{
	unsigned int	i;
	t_vector2		offset;

	offset.x = scene->center.x - scene->map->center.x;
	offset.y = scene->center.y - scene->map->center.y;
	i = 0;
	while (i < scene->map->vertices)
	{
		scene->map->iso_mesh[i].x += offset.x;
		scene->map->iso_mesh[i].y += offset.y;
		i++;
	}
	set_barycenter_mesh(scene);
}