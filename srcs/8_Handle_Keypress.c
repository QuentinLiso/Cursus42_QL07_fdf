#include "fdf.h"

int	handle_keypress_input(int keysym, t_scene *scene)
{
	handle_color_input(keysym, scene->map);
	handle_rotation_input(keysym, scene->map);
	if (keysym == XK_Escape)
		closing_window(scene);
	else if (keysym == XK_Left)
		scene->map->translation.x -= 10.0f;
	else if (keysym == XK_Right)
		scene->map->translation.x += 10.0f;
	else if (keysym == XK_Up)
		scene->map->translation.y -= 10.0f;
	else if (keysym == XK_Down)
		scene->map->translation.y += 10.0f;
	else if (keysym == XK_f)
		centering_mesh(scene->map);
	else if (keysym == XK_i)
		zoom_in(scene->map);
	else if (keysym == XK_o)
		zoom_out(scene->map);
	else if (keysym == XK_v)
		scene->map->iso = !scene->map->iso;
	return (1);
}

int	handle_rotation_input(int keysym, t_map *map)
{
	if (keysym == XK_x)
		rotate_3d_mesh(map, 10, X_AXIS);
	else if (keysym == XK_y)
		rotate_3d_mesh(map, 10, Y_AXIS);
	else if (keysym == XK_z)
		rotate_3d_mesh(map, 10, Z_AXIS);
	return (1);
}

int	handle_color_input(int keysym, t_map *map)
{
	if (keysym == XK_r)
		map->color = RED;
	else if (keysym == XK_g)
		map->color = GREEN;
	else if (keysym == XK_j)
		map->color = YELLOW;
	else if (keysym == XK_p)
		map->color = PINK;
	else if (keysym == XK_w)
		map->color = WHITE;
	return (1);
}
