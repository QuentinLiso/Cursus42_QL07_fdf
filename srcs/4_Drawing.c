/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_Drawing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:46 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:07:47 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_line_to_img(t_img *img, t_vector2 a, t_vector2 b, int color)
{
	double	dx;
	double	dy;
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
		i -= 8;
	}
}

int	draw_background(t_scene *scene, t_img *img, int color)
{
	int	w;
	int	h;

	h = 0;
	while (h < scene->win_h)
	{
		w = scene->cmds_w;
		while (w < scene->win_w)
		{
			put_pix_to_img(img, w, h, color);
			w++;
		}
		h++;
	}
	return (0);
}

int	draw_rect(t_img *img, t_rect rect)
{
	int	w;
	int	h;

	h = rect.y;
	while (h < rect.y + rect.height)
	{
		w = rect.x;
		while (w < rect.x + rect.width)
		{
			put_pix_to_img(img, w, h, rect.color);
			w++;
		}
		h++;
	}
	return (0);
}

void	draw_instructions(t_scene *scene, int color)
{
	draw_rect(&scene->img, (t_rect){0.0f, 0.0f, scene->cmds_w,
		scene->cmds_h, color});
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 20, 30, WHITE,
		"#############  COMMANDS  #############");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 50, WHITE,
		"View iso/front : v");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 70, WHITE,
		"Translate : arrows");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 90, WHITE,
		"Rotate : x / y / z");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 110, WHITE,
		"Zoom in/out : i / o");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 130, WHITE,
		"Center : f");
	mlx_string_put(scene->mlx_disp, scene->mlx_win, 50, 150, WHITE,
		"Switch colors : rgjpw");
}
