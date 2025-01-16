/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:14 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:07:16 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_map	map;

	if (ac == 2)
	{
		ft_bzero(&scene, sizeof(t_scene));
		init_scene(&scene, &map, av[1]);
		set_map_sizes(&scene, (&scene)->map->sourcefile);
		validate_map_sizes(&scene, scene.map->sourcefile);
		parse_map_values(scene.map, scene.map->sourcefile);
		set_vertices(scene.map);
		set_3d_raw_mesh(scene.map, scene.map->zoom);
		set_3d_iso_mesh(scene.map);
		set_display_elems(&scene);
		set_loops(&scene);
	}
	else
	{
		log_err("Wrong number of args !");
	}
	return (0);
}
