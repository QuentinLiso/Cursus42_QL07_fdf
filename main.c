#include "fdf.h"

void	pix_square(t_scene *scene, int x, int y, int color);
void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color);

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	t_scene	scene;


	return (0);
}



void	my_mlx_pixel_put(t_scene *scene, int x, int y, int color)
{
	char	*dst;

	dst = scene->addr + (y * scene->size_line + x * (scene->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	pix_square(t_scene *scene, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			my_mlx_pixel_put(scene, i, j, color);
			j++;
			//printf("Drawing at : i = %d ; j = %d\n", i, j);
		}
		i++;
		//printf("Sortie de boucle : i = %d, x = %d", i, x);
	}
}