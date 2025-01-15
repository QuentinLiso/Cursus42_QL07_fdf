/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_Zoom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 04:08:32 by qzoli             #+#    #+#             */
/*   Updated: 2024/12/29 04:08:34 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->iso_mesh[i].x *= map->zoom_coeff;
		map->iso_mesh[i].y *= map->zoom_coeff;
		map->iso_mesh[i].z *= map->zoom_coeff;
		i++;
	}
}

void	zoom_out(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->vertices)
	{
		map->iso_mesh[i].x /= map->zoom_coeff;
		map->iso_mesh[i].y /= map->zoom_coeff;
		map->iso_mesh[i].z /= map->zoom_coeff;
		i++;
	}
}
