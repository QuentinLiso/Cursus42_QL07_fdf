#include "fdf.h"

void	rotate_3d_point_x(t_vector3 *point, int angle)
{
	t_vector3	buf;

	buf.x = point->x;
	buf.y = point->y * cos_deg(angle) - point->z * sin_deg(angle);
	buf.z = point->y * sin_deg(angle) + point->z * cos_deg(angle);
	point->x = buf.x;
	point->y = buf.y;
	point->z = buf.z;
}

void	rotate_3d_point_y(t_vector3 *point, int angle)
{
	t_vector3	buf;

	buf.x = point->x * cos_deg(angle) + point->z * sin_deg(angle);
	buf.y = point->y;
	buf.z = -point->x * sin_deg(angle) + point->z * cos_deg(angle);
	point->x = buf.x;
	point->y = buf.y;
	point->z = buf.z;
}

void	rotate_3d_point_z(t_vector3 *point, int angle)
{
	t_vector3	buf;

	buf.x = point->x * cos_deg(angle) - point->y * sin_deg(angle);
	buf.y = point->x * sin_deg(angle) + point->y * cos_deg(angle);
	buf.z = point->z;
	point->x = buf.x;
	point->y = buf.y;
	point->z = buf.z;
}

void	rotate_3d_mesh(t_map *map, int angle, int axis)
{
	unsigned int	i;

	i = 0;
	if (axis == X_AXIS)
		while (i < map->vertices)
			rotate_3d_point_x(&map->raw_mesh[i++], angle);
	else if (axis == Y_AXIS)
		while (i < map->vertices)
			rotate_3d_point_y(&map->raw_mesh[i++], angle);
	else if (axis == Z_AXIS)
		while (i < map->vertices)
			rotate_3d_point_z(&map->raw_mesh[i++], angle);
}
