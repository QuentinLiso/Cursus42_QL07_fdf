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
}
