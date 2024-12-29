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
	if (scene->map->iso)
		set_2d_iso_mesh(scene->map);
	else
		set_2d_front_mesh(scene->map);
	draw_background(scene, &scene->img, DARK);
	render_2d_vertices(scene, WHITE);
	mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win,
		scene->img.mlx_img, 0, 0);
	draw_instructions(scene, DARK_BLUE);
	scene->to_update = FALSE;
	return (0);
}

int	render_2d_vertices(t_scene *scene, int color)
{
	unsigned int	i;
	t_vector2		cur;
	t_vector2		next;

	i = 0;
	while (i < scene->map->vertices)
	{
		cur.x = scene->map->iso_mesh[i].x;
		cur.y = scene->map->iso_mesh[i].y;
		put_pix_to_img(&scene->img, cur.x, cur.y, color);
		if (i % scene->map->width != scene->map->width - 1)
		{
			next.x = scene->map->iso_mesh[i + 1].x;
			next.y = scene->map->iso_mesh[i + 1].y;
			put_line_to_img(&scene->img, cur, next, scene->map->color);
		}
		if (i < scene->map->vertices - scene->map->width)
		{
			next.x = scene->map->iso_mesh[i + scene->map->width].x;
			next.y = scene->map->iso_mesh[i + scene->map->width].y;
			put_line_to_img(&scene->img, cur, next, scene->map->color);
		}
		i++;
	}
	return (0);
}
