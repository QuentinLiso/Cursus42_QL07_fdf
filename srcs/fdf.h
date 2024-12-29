/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:13:04 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:13:05 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define CMDS_WIDTH	300
# define CMDS_HEIGHT WINDOW_HEIGHT

# define MLX_ERROR 1
# define PI 3.141592654

# define PURPLE 0xE1D8ED
# define BLACK 0x000000
# define DARK 0x0F0F0F
# define DARK_BLUE 0x232D3F
# define WHITE 0xFBFAFC
# define RED 0x992E24
# define YELLOW 0xFFE26F
# define PINK 0xFDADC7
# define GREEN 0xC5F0A4

# define X_AXIS 1
# define Y_AXIS 2
# define Z_AXIS 3

# define FALSE 0
# define TRUE 1

typedef unsigned char	t_bool;

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_rect
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_rect;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	char	*img_file;
}	t_img;

typedef struct s_map
{
	char				*sourcefile;
	unsigned int		w_index;
	unsigned int		h_index;
	unsigned int		width;
	unsigned int		height;
	int					**sizes;
	double				zoom;
	double				zoom_coeff;
	unsigned int		vertices;
	t_vector2			translation;
	t_vector2			*iso_mesh;
	t_vector3			*raw_mesh;
	t_vector3			center;
	int					color;
	t_bool				iso;
}	t_map;

typedef struct s_scene
{
	void				*mlx_disp;
	void				*mlx_win;
	t_img				img;
	t_map				*map;
	t_vector2			center;
	t_bool				to_update;
	int					win_w;
	int					win_h;
	int					cmds_w;
	int					cmds_h;
}	t_scene;

void	init_scene(t_scene *scene, t_map *map, char *av);
void	set_map_sizes(t_scene *scene, char *sourcefile);
void	trim_map_line(char **line, char c);
void	validate_map_sizes(t_scene *scene, char *sourcefile);
void	parse_map_values(t_map *map, char *sourcefile);

void	log_err(char *log_msg);
double	cos_deg(double degree);
double	sin_deg(double degree);
//void	print_map_values(t_scene *scene);
//void	print_3d_raw_mesh(t_scene *scene);
//void	print_2d_iso_mesh(t_scene *scene);

void	set_vertices(t_map *map);
void	set_3d_raw_mesh(t_map *map, int step);
void	set_2d_iso_mesh(t_map *map);
void	set_2d_front_mesh(t_map *map);
void	centering_mesh(t_map *map);

void	put_line_to_img(t_img *img, t_vector2 a, t_vector2 b, int color);
void	put_pix_to_img(t_img *img, int x, int y, int color);
int		draw_background(t_scene *scene, t_img *img, int color);
int		draw_rect(t_img *img, t_rect rect);
void	draw_instructions(t_scene *scene, int color);

int		set_display_elems(t_scene *scene);
int		set_loops(t_scene *scene);
int		update_render(t_scene *scene);
int		render_2d_vertices(t_scene *scene, int color);

void	rotate_3d_point_x(t_vector3 *point, int angle);
void	rotate_3d_point_y(t_vector3 *point, int angle);
void	rotate_3d_point_z(t_vector3 *point, int angle);
void	rotate_3d_mesh(t_map *map, int angle, int axis);

void	zoom_in(t_map *map);
void	zoom_out(t_map *map);

int		handle_keypress_input(int keysym, t_scene *scene);
int		handle_rotation_input(int keysym, t_map *map);
int		handle_color_input(int keysym, t_map *map);
int		closing_window(t_scene *scene);

#endif
