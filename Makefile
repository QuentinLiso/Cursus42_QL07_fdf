SRCS=$(addsuffix .c, fichier1 fichier2 fichier3 fichier4 fichier5 fichier6 fichier7)

all :
	cc -Wall -Wextra -Werror -I./minilibx-linux -I./libft/includes maintest.c $(SRCS) -lmlx -lXext -lX11 -lft -lm -L./minilibx-linux -L./libft -g

real :
	cc -Wall -Wextra -Werror -I./minilibx-linux -I./libft/includes main.c $(SRCS) -lmlx -lXext -lX11 -lft -lm -L./minilibx-linux -L./libft