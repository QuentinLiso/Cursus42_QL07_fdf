#include "fdf.h"

void	translate_iso_mesh(t_scene *scene, t_vector2 translation)
{
	unsigned int	i;

	i = 0;
	while (i < scene->map->vertices)
	{
		scene->map->iso_mesh[i].x += (translation.x * scene->map->translation);
		scene->map->iso_mesh[i].y += (translation.y * scene->map->translation);
		i++;
	}
	set_barycenter_mesh(scene);
}

void	rotate_iso_mesh(t_scene *scene, int angle)
{
	unsigned int	i;
	t_vector3		*buf;

	i = 0;
	buf = ft_calloc(scene->map->vertices, sizeof(t_vector3));
	if (!buf)
	{
		log_err("Malloc failed in rotation");
	}
	while (i < scene->map->vertices)
	{
		buf[i].x = scene->map->raw_mesh[i].x * cos_deg(angle) - scene->map->raw_mesh[i].y * sin_deg(angle);
		buf[i].y = scene->map->raw_mesh[i].x * sin_deg(angle) + scene->map->raw_mesh[i].y * cos_deg(angle);;
		buf[i].z = scene->map->raw_mesh[i].z;
		i++;
	}
	free(scene->map->raw_mesh);
	scene->map->raw_mesh = buf;
	set_2d_iso_mesh(scene);
	set_barycenter_mesh(scene);
	free(buf);
}











void	zoom_in(t_scene *scene)
{
	t_vector2		offset_barycentre;
	unsigned int	i;

	offset_barycentre = (t_vector2){0.0f, 0.0f};
	i = 0;
	while (i < scene->map->vertices)
	{
		if (i == 0)
			printf("i0 : %f %f ", scene->map->iso_mesh[i].x, scene->map->iso_mesh[i].y);
		offset_barycentre.x = scene->map->iso_mesh[i].x - scene->map->center.x;
		offset_barycentre.y = scene->map->iso_mesh[i].y - scene->map->center.y;
		offset_barycentre.x *= scene->map->zoom_coeff;
		offset_barycentre.y *= scene->map->zoom_coeff;
		scene->map->iso_mesh[i].x += offset_barycentre.x;
		scene->map->iso_mesh[i].y += offset_barycentre.y;
		if (i == 0)
			printf("i0 : %f %f ", scene->map->iso_mesh[i].x, scene->map->iso_mesh[i].y);
		i++;
	}
}

void	zoom_out(t_scene *scene)
{
	t_vector2		offset_barycentre;
	unsigned int	i;

	offset_barycentre = (t_vector2){0.0f, 0.0f};
	i = 0;
	while (i < scene->map->vertices)
	{
		offset_barycentre.x = scene->map->iso_mesh[i].x - scene->map->center.x;
		offset_barycentre.y = scene->map->iso_mesh[i].y - scene->map->center.y;
		offset_barycentre.x /= scene->map->zoom_coeff;
		offset_barycentre.y /= scene->map->zoom_coeff;
		scene->map->iso_mesh[i].x += offset_barycentre.x;
		scene->map->iso_mesh[i].y += offset_barycentre.y;
		i++;
	}
}

