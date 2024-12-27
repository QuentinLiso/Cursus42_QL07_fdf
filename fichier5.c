#include "fdf.h"

int	set_display_elems(t_scene *scene)
{
	scene->map->h_index = 0;
	scene->mlx_disp = mlx_init();
	if (!scene->mlx_disp)
		exit(MLX_ERROR);
	scene->mlx_win = mlx_new_window(scene->mlx_disp, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window");
	if (!scene->mlx_win)
		exit(MLX_ERROR);
	scene->img.mlx_img = mlx_new_image(scene->mlx_disp, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!scene->img.mlx_img)
		exit(MLX_ERROR);
	scene->img.addr = mlx_get_data_addr(scene->img.mlx_img, 
					&(scene->img.bpp), &(scene->img.size_line), &(scene->img.endian));
	mlx_loop_hook(scene->mlx_disp, &update_render, scene);
	mlx_hook(scene->mlx_win, KeyPress, KeyPressMask, &handle_keypress_input, scene);
	mlx_hook(scene->mlx_win, DestroyNotify, Button1Mask, &closing_window, scene);
	mlx_loop(scene->mlx_disp);
	return (0);
}

int	update_render(t_scene *scene)
{
	if (scene->mlx_win == NULL)
		return (1);
	render_background(&scene->img, BLACK);
	render_2d_vertices(scene, WHITE);
	//render_instructions(scene);
	mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win, scene->img.mlx_img, 0, 0);
	//mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win, scene->cmds_img.mlx_img, 0, 0);
	return (0);
}

int		render_2d_vertices(t_scene *scene, int color)
{
	unsigned int 		i;
	t_vector2	cur;
	t_vector2	next;

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
			put_line_to_img(&scene->img, cur, next, WHITE);
		}
		if (i < scene->map->vertices - scene->map->width)
		{
			next.x = scene->map->iso_mesh[i + scene->map->width].x;
			next.y = scene->map->iso_mesh[i + scene->map->width].y;
			put_line_to_img(&scene->img, cur, next, WHITE);
		}
		i++;
	}
	return (0);
}

int	closing_window(t_scene *scene)
{
	mlx_destroy_window(scene->mlx_disp, scene->mlx_win);
	mlx_destroy_display(scene->mlx_disp);
	free(scene->mlx_disp);
	free(scene->img.mlx_img);
	//free(scene->cmds_img.mlx_img);
	free(scene->map->iso_mesh);
	free(scene->map->raw_mesh);
	exit (1);
}