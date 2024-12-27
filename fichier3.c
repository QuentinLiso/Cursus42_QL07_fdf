#include "fdf.h"

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

void	put_pix_to_img(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || y < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return ;
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
