/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_Utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:07:29 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:07:30 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	log_err(char *log_msg)
{
	ft_putendl_fd(log_msg, 2);
	exit (1);
}

double	cos_deg(double degree)
{
	double	rad;

	rad = degree * PI / 180;
	return (cos(rad));
}

double	sin_deg(double degree)
{
	double	rad;

	rad = degree * PI / 180;
	return (sin(rad));
}

/*
void	print_map_values(t_scene *scene)
{
	unsigned int h;
	unsigned int w;

	ft_printf("Width : %d\n", scene->map->width);
	ft_printf("Height : %d\n", scene->map->height);
	h = 0;
	while (h < scene->map->height)
	{
		w = 0;
		while (w < scene->map->width)
		{
			ft_printf("[%d, %d] = %d\n", w, h, scene->map->sizes[h][w]);
			w++;
		}
		h++;
	}
}

void	print_3d_raw_mesh(t_scene *scene)
{
	unsigned int	i;

	i = 0;
	while (i < scene->map->width * scene->map->height)
	{
		printf("(%f, ", scene->map->raw_mesh[i].x);
		printf("%f, ", scene->map->raw_mesh[i].y);
		printf("%f)\n", scene->map->raw_mesh[i].z);
		i++;
	}
}
*/
