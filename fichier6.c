#include "fdf.h"

int	handle_keypress_input(int keysym, t_scene *scene)
{
	(void)scene;
	if (keysym == XK_Escape)
		closing_window(scene);
	else if (keysym == XK_Left)
		translate_iso_mesh(scene, (t_vector2){-1.0f, 0.0f});
	else if (keysym == XK_Right)
		translate_iso_mesh(scene, (t_vector2){1.0f, 0.0f});
	else if (keysym == XK_Up)
		translate_iso_mesh(scene, (t_vector2){0.0f, -1.0f});
	else if (keysym == XK_Down)
		translate_iso_mesh(scene, (t_vector2){0.0f, 1.0f});
	else if(keysym == XK_f)
		centering_mesh(scene);
	else if(keysym == XK_x)
		rotate_iso_mesh(scene, -30);
	mlx_clear_window(scene->mlx_disp, scene->mlx_win);
	//mlx_destroy_image(scene->mlx_disp, scene->img.mlx_img);
	return (1);
	//return(ft_printf("%d\n", keysym));
}