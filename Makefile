SRCS=$(addprefix ./srcs/, $(addsuffix .c, 0_main 1_Init 2_Utils 3_Set_meshes 4_Drawing 5_Rendering 6_Rotation 7_Zoom 8_Handle_Keypress))

all :
	cc -Wall -Wextra -Werror -I./minilibx-linux -I./libft/includes $(SRCS) -lmlx -lXext -lX11 -lft -lm -L./minilibx-linux -L./libft -g3
