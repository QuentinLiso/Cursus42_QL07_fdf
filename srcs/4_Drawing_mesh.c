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

void	put_line_to_img(t_img *img, t_vector3 u, t_vector3 v, t_map *map)
{
	t_vector2	d;
	int			pixels;
	t_vector2	iso[2];
	int			color;

	if (u.level > v.level)
		color = u.color;
	else
		color = v.color;
	iso_vect(&iso, u, v, map);
	d.x = iso[1].x - iso[0].x;
	d.y = iso[1].y - iso[0].y;
	pixels = sqrt(d.x * d.x + d.y * d.y);
	d.x /= pixels;
	d.y /= pixels;
	while (pixels)
	{
		put_pix_to_img(img, iso[0].x, iso[0].y, color);
		iso[0].x += d.x;
		iso[0].y += d.y;
		--pixels;
	}
}

void	iso_vect(t_vector2 (*iso)[2], t_vector3 u, t_vector3 v, t_map *map)
{
	if (map->iso)
	{
		(*iso)[0].x = cos_deg(30.0f) * u.x - cos_deg(30.0f) * u.y;
		(*iso)[0].y = sin_deg(30.0f) * u.x + sin_deg(30.0f) * u.y - u.z;
		(*iso)[1].x = cos_deg(30.0f) * v.x - cos_deg(30.0f) * v.y;
		(*iso)[1].y = sin_deg(30.0f) * v.x + sin_deg(30.0f) * v.y - v.z;
	}
	else
	{
		(*iso)[0].x = u.x;
		(*iso)[0].y = -u.z;
		(*iso)[1].x = v.x;
		(*iso)[1].y = -v.z;
	}
	(*iso)[0].x += map->translation.x + WINDOW_WIDTH / 2;
	(*iso)[0].y += map->translation.y + WINDOW_HEIGHT / 2;
	(*iso)[1].x += map->translation.x + WINDOW_WIDTH / 2;
	(*iso)[1].y += map->translation.y + WINDOW_HEIGHT / 2;
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
