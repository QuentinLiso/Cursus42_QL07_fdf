#include "fdf.h"

void	log_err(char *log_msg)
{
	ft_putendl_fd(log_msg, 2);
	exit (1);
}

//---------------------------------------------------------

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
	while (buf[scene->width])
	{
		free(buf[scene->width]);
		scene->width++;
	}
	while (line)
	{
		free(line);
		scene->height++;
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
		scene->w_index = 0;
		while (buf[scene->w_index])
		{
			free(buf[scene->w_index]);
			scene->w_index++;
		}
		free(buf);
		if (scene->w_index != scene->width)
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
	scene->sizes = ft_calloc(scene->height, sizeof(int *));
	if (!scene->sizes)
		log_err("Parsing malloc failed!");
	while (scene->h_index < scene->height)
	{
		scene->sizes[scene->h_index] = ft_calloc(scene->width, sizeof(int));
		if (!scene->sizes[scene->h_index])
			log_err("Parsing malloc failed");
		line = get_next_line(fd);
		trim_map_line(&line, '\n');
		buf = ft_split(line, ' ');
		free(line);
		scene->w_index = -1;
		while (++scene->w_index < scene->width)
		{
			scene->sizes[scene->h_index][scene->w_index] = ft_atoi(buf[scene->w_index]);
			free(buf[scene->w_index]);
		}
		scene->h_index++;
		free(buf);
	}
}

void	print_map_values(t_scene *scene)
{
	unsigned int h;
	unsigned int w;

	ft_printf("Width : %d\n", scene->width);
	ft_printf("Height : %d\n", scene->height);
	h = 0;
	while (h < scene->height)
	{
		w = 0;
		while (w < scene->width)
		{
			ft_printf("[%d, %d] = %d\n", w, h, scene->sizes[h][w]);
			w++;
		}
		h++;
	}
}

void	set_3d_raw_mesh(t_scene *scene)
{
	unsigned int		i;

	scene->raw_mesh = ft_calloc(scene->height * scene->width, sizeof(t_vector3));
	if (!scene->raw_mesh)
		log_err("Set 3D mesh Malloc failed!");
	i = 0;
	scene->h_index = 0;
	while (scene->h_index < scene->height)
	{
		scene->w_index = 0;
		while (scene->w_index < scene->width)
		{
			scene->raw_mesh[i].x = scene->w_index * scene->step;
			scene->raw_mesh[i].y = scene->h_index * scene->step;
			scene->raw_mesh[i].z = scene->sizes[scene->h_index][scene->w_index];
			i++;
			scene->w_index++;
		}
		free(scene->sizes[scene->h_index]);
		scene->h_index++;
	}
	free(scene->sizes);
}


void	print_3d_raw_mesh(t_scene *scene)
{
	unsigned int	i;

	i = 0;
	while (i < scene->width * scene->height)
	{
		printf("(%f, ", scene->raw_mesh[i].x);
		printf("%f, ", scene->raw_mesh[i].y);
		printf("%f)\n", scene->raw_mesh[i].z);
		i++;
	}
}