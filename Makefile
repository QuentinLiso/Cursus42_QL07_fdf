

all :
	cc -Wall -Wextra -Werror -I./minilibx-linux -I./libft/includes maintest.c srcs.c -lmlx -lXext -lX11 -lft -lm -L./minilibx-linux -L./libft

real :
	cc -Wall -Wextra -Werror -I./minilibx-linux -I./libft/includes main.c srcs.c -lmlx -lXext -lX11 -lft -lm -L./minilibx-linux -L./libft