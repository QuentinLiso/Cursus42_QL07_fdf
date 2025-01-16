/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_Init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:22 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:07:23 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_scene(t_scene *scene, t_map *map, char *av)
{
	scene->map = map;
	scene->map->sourcefile = av;
	scene->map->width = 0;
	scene->map->height = 0;
	scene->map->h_index = -1;
	scene->map->iso = 1;
	scene->map->translation = (t_vector2){0.0f, 0.0f};
	scene->map->zoom = 35;
	scene->map->zoom_coeff = 1.25f;
	scene->map->color_1 = BLUE;
	scene->map->color_2 = GREEN;
	scene->to_update = TRUE;
	scene->win_w = WINDOW_WIDTH;
	scene->win_h = WINDOW_HEIGHT;
	scene->cmds_w = CMDS_WIDTH;
	scene->cmds_h = CMDS_HEIGHT;
}

void	set_map_sizes(t_scene *scene, char *sourcefile)
{
	int		fd;
	char	*line;
	char	**buf;

	fd = open(sourcefile, O_RDONLY);
	if (fd < 0)
		log_err("Map file not opened!");
	line = get_next_line(fd);
	if (!line)
		log_err("Map file is empty!");
	trim_map_line(&line, '\n');
	buf = ft_split(line, ' ');
	while (buf[scene->map->width])
		free(buf[scene->map->width++]);
	while (line)
	{
		free(line);
		scene->map->height++;
		line = get_next_line(fd);
	}
	free(line);
	free(buf);
	close(fd);
}

void	trim_map_line(char **line, char c)
{
	size_t	line_len;

	line_len = ft_strlen(*line);
	if ((*line)[line_len - 1] == c)
		(*line)[line_len -1] = '\0';
}

void	validate_map_sizes(t_scene *scene, char *sourcefile)
{
	int		fd;
	char	*line;
	char	**buf;

	fd = open(sourcefile, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		trim_map_line(&line, '\n');
		buf = ft_split(line, ' ');
		free(line);
		scene->map->w_index = 0;
		while (buf[scene->map->w_index])
			free(buf[scene->map->w_index++]);
		free(buf);
		if (scene->map->w_index != scene->map->width)
			log_err("Map lines sizes non consistent!");
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	parse_map_values(t_map *map, char *sourcefile)
{
	int		fd;
	char	*line;
	char	**buf;

	fd = open(sourcefile, O_RDONLY);
	map->sizes = ft_calloc(map->height, sizeof(int *));
	if (!map->sizes)
		log_err("Parsing malloc failed!");
	while (++map->h_index < map->height)
	{
		map->sizes[map->h_index] = ft_calloc(map->width, sizeof(int));
		if (!map->sizes[map->h_index])
			log_err("Parsing malloc failed");
		line = get_next_line(fd);
		trim_map_line(&line, '\n');
		buf = ft_split(line, ' ');
		free(line);
		map->w_index = -1;
		while (++map->w_index < map->width)
		{
			map->sizes[map->h_index][map->w_index] = ft_atoi(buf[map->w_index]);
			free(buf[map->w_index]);
		}
		free(buf);
	}
}
