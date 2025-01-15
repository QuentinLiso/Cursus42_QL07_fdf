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

void	put_line_to_img(t_img *img, t_vector3 u, t_vector3 v, int color)
{
	t_vector2	d;
	int		pixels;
	t_vector2	a;
	t_vector2	b;

	if (u.z != 0 || v.z != 0)
		color = RED;
	else
		color = WHITE;

	a.x = cos_deg(30.0f) * u.x - cos_deg(30.0f) * u.y;
	a.y = sin_deg(30.0f) * u.x + sin_deg(30.0f) * u.y - u.z;
	a.x += /*map->translation.x +*/ WINDOW_WIDTH / 2;
	a.y += /*map->translation.y +*/ WINDOW_HEIGHT / 2;
	b.x = cos_deg(30.0f) * v.x - cos_deg(30.0f) * v.y;
	b.y = sin_deg(30.0f) * v.x + sin_deg(30.0f) * v.y - v.z;
	b.x += /*map->translation.x +*/ WINDOW_WIDTH / 2;
	b.y += /*map->translation.y +*/ WINDOW_HEIGHT / 2;

	d.x = b.x - a.x;
	d.y = b.y - a.y;
	pixels = sqrt(d.x * d.x + d.y * d.y);
	d.x /= pixels;
	d.y /= pixels;
	while (pixels)
	{
		put_pix_to_img(img, a.x, a.y, color);
		a.x += d.x;
		a.y += d.y;
		--pixels;
	}
}


t_vector2	iso_vect(t_vector3 u, t_map *map)
{
	t_vector2	iso_u;

	iso_u.x = cos_deg(30.0f) * u.x - cos_deg(30.0f) * u.y;
	iso_u.y = sin_deg(30.0f) * u.x + sin_deg(30.0f) * u.y - u.z;
	iso_u.x += map->translation.x + WINDOW_WIDTH / 2;
	iso_u.y += map->translation.y + WINDOW_HEIGHT / 2;
	return (iso_u);
}

void	new_draw_line(t_img *img, t_vector3 a, t_vector3 b, t_map *map)
{
	t_vector2	d;
	double		pixels;
	t_vector2	iso[2];

	if (a.z || b.z)
		map->color = RED;
	else
		map->color = WHITE;
	iso[0] = iso_vect(a, map);
	iso[1] = iso_vect(b, map);
	d.x = iso[1].x - iso[0].x;
	d.y = iso[1].y - iso[0].y;
	pixels = sqrt(d.x * d.x + d.y * d.y);
	d.x /= pixels;
	d.y /= pixels;
	while (pixels)
	{
		put_pix_to_img(img, iso[0].x, iso[0].y, map->color);
		iso[0].x += d.x;
		iso[0].y += d.y;
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
