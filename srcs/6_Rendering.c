/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_Rendering.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:54 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:08:16 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_display_elems(t_scene *scene)
{
	scene->map->h_index = 0;
	scene->mlx_disp = mlx_init();
	if (!scene->mlx_disp)
		exit(MLX_ERROR);
	scene->mlx_win = mlx_new_window(scene->mlx_disp,
			WINDOW_WIDTH, WINDOW_HEIGHT, "FDF by QLISO");
	if (!scene->mlx_win)
	{
		free(scene->mlx_disp);
		exit(MLX_ERROR);
	}
	scene->img.mlx_img = mlx_new_image(scene->mlx_disp,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!scene->img.mlx_img)
	{
		free(scene->mlx_win);
		free(scene->mlx_disp);
		exit(MLX_ERROR);
	}
	scene->img.addr = mlx_get_data_addr(scene->img.mlx_img,
			&(scene->img.bpp), &(scene->img.size_line), &(scene->img.endian));
	return (0);
}

int	set_loops(t_scene *scene)
{
	mlx_loop_hook(scene->mlx_disp, &update_render, scene);
	mlx_hook(scene->mlx_win, KeyPress, KeyPressMask,
		&handle_keypress_input, scene);
	mlx_hook(scene->mlx_win, DestroyNotify, Button1Mask,
		&closing_window, scene);
	mlx_loop(scene->mlx_disp);
	return (0);
}

int	update_render(t_scene *scene)
{
	if (scene->to_update == FALSE)
		return (0);
	if (scene->mlx_win == NULL)
		return (1);
	draw_background(scene, &scene->img, DARK);
	render_2d(scene);
	mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win,
		scene->img.mlx_img, 0, 0);
	draw_instructions(scene, DARK_BLUE);
	scene->to_update = FALSE;
	return (0);
}

int	render_2d(t_scene *scene)
{
	t_vector3		*v;
	unsigned int	i;

	v = scene->map->iso_mesh;
	i = 0;
	while (i < scene->map->vertices)
	{
		if (i % scene->map->width != scene->map->width - 1)
			put_line_to_img(&scene->img, v[i], v[i + 1], scene->map);
		if (i < scene->map->vertices - scene->map->width)
			put_line_to_img(&scene->img, v[i], v[i + scene->map->width], scene->map);
		i++;
	}
	return (0);
}

