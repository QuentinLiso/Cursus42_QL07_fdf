#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define STEP 10
# define CMDS_WIDTH	400
# define CMDS_HEIGHT WINDOW_HEIGHT
# define CMDS_FILE "./imgs/fdf.xpm"
//# define ESCAPE_KEY 65307
# define MLX_ERROR 1

# define PURPLE 0xE1D8ED
# define WHITE 0xFBFAFC
# define BLACK 0x000000

typedef struct s_scene		t_scene;
typedef struct s_vector2	t_vector2;
typedef struct s_vector3	t_vector3;
typedef struct s_rect		t_rect;
typedef struct s_img		t_img;

struct s_vector2
{
	double x;
	double y;
};

struct s_vector3
{
	double	x;
	double	y;
	double	z;
};

struct s_rect
{
	double x;
	double y;
	double width;
	double	height;
	int		color;
};

struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	char	*img_file;
};

struct s_scene
{
	void				*mlx_disp;
	void 				*mlx_win;
	t_img				img;
	t_img				cmds_img;

	char				*sourcefile;
	unsigned int		w_index;
	unsigned int		h_index;
	unsigned int		width;
	unsigned int		height;
	int					**sizes;
	unsigned int		step;
	t_vector2			*iso_mesh;
	t_vector3			*raw_mesh;
};

void	log_err(char *log_msg);



#endif