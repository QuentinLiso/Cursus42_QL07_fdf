#include "fdf.h"

void	set_map_sizes(t_scene *scene, char *sourcefile);
void	validate_map_sizes(t_scene *scene, char *sourcefile);
void	parse_map_values(t_scene *scene, char *sourcefile);
void	print_map_values(t_scene *scene);
void	set_3d_raw_mesh(t_scene *scene);
void	print_3d_raw_mesh(t_scene *scene);
int		set_display_elems(t_scene *scene);
int		update_render(t_scene *scene);
int		render_background(t_img *img, int color);
int		render_rect(t_img *img, t_rect rect);
void	put_pix_to_img(t_img *img, int x, int y, int color);
int		render_map(t_scene *scene, int color);
void	put_map_points_to_img(t_scene *scene, int color);
void	put_line_to_img(t_img *img, t_vector2 a, t_vector2 b, int color);
void	render_instructions(t_scene *scene);
int		handle_keypress_input(int keycode, t_scene *scene);
int		closing_window(t_scene *scene);

int	main(int ac, char **av)
{
	t_scene	scene;

	scene.sourcefile = av[1];
	scene.width = 0;
	scene.height = 0;
	scene.h_index = 0;
	scene.step = 10;

	if (ac == 2)
	{
		set_map_sizes(&scene, scene.sourcefile);
		validate_map_sizes(&scene, scene.sourcefile);
		parse_map_values(&scene, scene.sourcefile);
		//print_map_values(&scene);
		set_3d_raw_mesh(&scene);
		print_3d_raw_mesh(&scene);
		set_display_elems(&scene);
	}
	else
	{
		log_err("Wrong number of args !");
	}
	return (0);
}

int	set_display_elems(t_scene *scene)
{
	scene->h_index = 0;
	scene->mlx_disp = mlx_init();
	if (!scene->mlx_disp)
	{
		free(scene->mlx_disp);
		return (MLX_ERROR);
	}
	scene->mlx_win = mlx_new_window(scene->mlx_disp, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window");
	if (!scene->mlx_win)
	{
		free(scene->mlx_win);
		return (MLX_ERROR);
	}
	scene->img.mlx_img = mlx_new_image(scene->mlx_disp, WINDOW_WIDTH, WINDOW_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.mlx_img, &(scene->img.bpp), &(scene->img.size_line), &(scene->img.endian));
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
	render_map(scene, WHITE);
	render_instructions(scene);
	//put_line_to_img(&scene->img, (t_vector2){600, 200}, (t_vector2){900, 400}, BLACK);
	mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win, scene->img.mlx_img, 0, 0);
	mlx_put_image_to_window(scene->mlx_disp, scene->mlx_win, scene->cmds_img.mlx_img, 0, 0);
	return (0);
}

void	put_pix_to_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->size_line + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i) & 0xFF);
		i-=8;
	}
}

int		render_map(t_scene *scene, int color)
{
	int	w;
	int	h;

	h = 0;
	while (h < (int)scene->height)
	{
		w = 0;
		while (w < (int)scene->width)
		{
			put_pix_to_img(&scene->img, w + WINDOW_WIDTH / 2, h + WINDOW_HEIGHT / 2, color);
			w++;
		}
		h++;
	}
	return (0);
}

void	put_line_to_img(t_img *img, t_vector2 a, t_vector2 b, int color)
{
	double 	dx;
	double 	dy;
	int		pixels;

	dx = b.x - a.x;
	dy = b.y - a.y;
	pixels = sqrt(dx * dx + dy * dy);
	dx /= pixels;
	dy /= pixels;
	while (pixels)
	{
		put_pix_to_img(img, a.x, a.y, color);
		a.x += dx;
		a.y += dy;
		--pixels;
	}
}

int		render_background(t_img *img, int color)
{
	int	w;
	int	h;

	h = 0;
	while (h < WINDOW_HEIGHT)
	{
		w = 0;
		while (w < WINDOW_WIDTH)
		{
			put_pix_to_img(img, w, h, color);
			w++;
		}
		h++;
	}
	return (0);
}

int		render_rect(t_img *img, t_rect rect)
{
	int	w;
	int	h;

	h = rect.y;
	while (h < rect.y + rect.width)
	{
		w = rect.x;
		while (w < rect.x + rect.height)
		{
			put_pix_to_img(img, w, h, rect.color);
			w++;
		}
		h++;
	}
	return (0);
}

void		render_instructions(t_scene *scene)
{
	int		*w;
	int		*h;
	char	*img_file;

	scene->cmds_img.width = CMDS_WIDTH;
	scene->cmds_img.height = CMDS_HEIGHT;
	scene->cmds_img.img_file = CMDS_FILE;
	w = &(scene->cmds_img.width);
	h = &(scene->cmds_img.height);
	img_file = scene->cmds_img.img_file;
	scene->cmds_img.mlx_img = mlx_xpm_file_to_image(scene->mlx_disp, img_file, h, w);
}

int	handle_keypress_input(int keysym, t_scene *scene)
{
	(void)scene;
	if (keysym == XK_Escape)
		closing_window(scene);
	return (1);
	//return(ft_printf("%d\n", keysym));
}

int	closing_window(t_scene *scene)
{
	mlx_destroy_window(scene->mlx_disp, scene->mlx_win);
	mlx_destroy_display(scene->mlx_disp);
	free(scene->mlx_disp);
	exit (1);
}


