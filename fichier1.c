#include "fdf.h"

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
	buf = ft_split(line, ' ');
	while (buf[scene->map->width])
	{
		free(buf[scene->map->width]);
		scene->map->width++;
	}
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
		{
			free(buf[scene->map->w_index]);
			scene->map->w_index++;
		}
		free(buf);
		if (scene->map->w_index != scene->map->width)
			log_err("Map lines sizes non consistent!");
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void parse_map_values(t_scene *scene, char *sourcefile)
{
	int		fd;
	char	*line;
	char	**buf;

	fd = open(sourcefile, O_RDONLY);
	scene->map->sizes = ft_calloc(scene->map->height, sizeof(int *));
	if (!scene->map->sizes)
		log_err("Parsing malloc failed!");
	while (scene->map->h_index < scene->map->height)
	{
		scene->map->sizes[scene->map->h_index] = ft_calloc(scene->map->width, sizeof(int));
		if (!scene->map->sizes[scene->map->h_index])
			log_err("Parsing malloc failed");
		line = get_next_line(fd);
		trim_map_line(&line, '\n');
		buf = ft_split(line, ' ');
		free(line);
		scene->map->w_index = -1;
		while (++scene->map->w_index < scene->map->width)
		{
			scene->map->sizes[scene->map->h_index][scene->map->w_index] = ft_atoi(buf[scene->map->w_index]);
			free(buf[scene->map->w_index]);
		}
		scene->map->h_index++;
		free(buf);
	}
}