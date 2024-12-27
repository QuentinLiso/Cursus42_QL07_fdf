#include "fdf.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_map	map;

	scene.map = &map;
	scene.map->sourcefile = av[1];
	scene.map->width = 0;
	scene.map->height = 0;
	scene.map->h_index = 0;
	scene.center = (t_vector2){CMDS_WIDTH + (WINDOW_WIDTH - CMDS_WIDTH) / 2, WINDOW_HEIGHT / 2};
	scene.map->step = 35;
	scene.map->zoom_coeff = 1.05f;
	scene.map->translation = 10.0f;

	if (ac == 2)
	{
		set_map_sizes(&scene, scene.map->sourcefile);
		validate_map_sizes(&scene, scene.map->sourcefile);
		parse_map_values(&scene, scene.map->sourcefile);
		//print_map_values(&scene);
		set_3d_raw_mesh(&scene, scene.map->step);
		//print_3d_raw_mesh(&scene);
		set_2d_iso_mesh(&scene);
		set_barycenter_mesh(&scene);
		centering_mesh(&scene);
		set_display_elems(&scene);
	}
	else
	{
		log_err("Wrong number of args !");
	}
	return (0);
}

