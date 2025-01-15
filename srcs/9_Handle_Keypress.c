/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_Handle_Keypress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:08:44 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:08:49 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress_input(int keysym, t_scene *scene)
{
	scene->to_update = TRUE;
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
		toggle_view(scene->map);
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
		map->color_2 = RED;
	else if (keysym == XK_b)
		map->color_2 = BLUE;
	else if (keysym == XK_j)
		map->color_2 = YELLOW;
	else if (keysym == XK_p)
		map->color_2 = PINK;
	else if (keysym == XK_w)
		map->color_2 = WHITE;
	return (1);
}

void	toggle_view(t_map *map)
{
	map->iso = !map->iso;
	set_3d_iso_mesh(map);
	map->translation.x = 0;
	map->translation.y = 0;
}

int	closing_window(t_scene *scene)
{
	free(scene->map->iso_mesh);
	free(scene->map->raw_mesh);
	mlx_destroy_image(scene->mlx_disp, (&scene->img)->mlx_img);
	mlx_destroy_window(scene->mlx_disp, scene->mlx_win);
	mlx_destroy_display(scene->mlx_disp);
	free(scene->mlx_disp);
	exit (0);
}
