#include "fdf.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_map	map;

	if (ac == 2)
	{
		init_scene(&scene, &map, av[1]);
		set_map_sizes(&scene, (&scene)->map->sourcefile);
		validate_map_sizes(&scene, scene.map->sourcefile);
		parse_map_values(scene.map, scene.map->sourcefile);
		set_3d_raw_mesh(scene.map, scene.map->zoom);
		set_2d_iso_mesh(scene.map);
		set_display_elems(&scene);
	}
	else
	{
		log_err("Wrong number of args !");
	}
	return (0);
}

