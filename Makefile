SRCS=$(addprefix ./srcs/, \
		$(addsuffix .c, \
			0_main 1_Init 2_Utils 3_Set_meshes 4_Drawing_mesh \
			5_Drawing_instructions 6_Rendering 7_Rotation 8_Zoom 9_Handle_Keypress\
		)\
	)
OBJ=$(SRCS:%.c=%.o)
HEADER=./srcs/fdf.h
NAME=fdf

LIB=libft.a
LIB_FOLD=./libft/
MLX=libmlx.a
MLX_FOLD=./minilibx-linux/

CCFLAGS=-Wall -Werror -Wextra
IFLAGS=-I./minilibx-linux -I./libft/includes
LFLAGS=-L./minilibx-linux -L./libft -lmlx -lXext -lX11 -lft -lm

.PHONY: all clean fclean re

YELLOW=\033[1;33m
WHITE=\033[0;37m

#-------------------------------------------

all 	: $(LIB) $(MLX) $(NAME) 


$(LIB)	: $(LIB_FOLD)$(LIB)

$(LIB_FOLD)$(LIB)	:
		@echo -e "$(YELLOW)\n\n🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒 COMPILING LIBFT 🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒\n\n$(WHITE)"
		make -C $(LIB_FOLD) all

$(MLX)	: $(MLX_FOLD)$(MLX)

$(MLX_FOLD)$(MLX)	:
		@echo -e "$(YELLOW)\n\n🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒 COMPILING MLX 🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒\n\n$(WHITE)"
		make -C $(MLX_FOLD)



$(NAME)	: $(OBJ)
		@echo -e "$(YELLOW)\n\n🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒 COMPILING FDF 🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒🦒\n\n$(WHITE)"
		$(CC) $(CCFLAGS) $(IFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

%.o		: %.c $(HEADER)
		$(CC) $(CCFLAGS) $(IFLAGS) -c $< -o $@

clean	:
		rm -rf $(OBJ)
		make -C $(LIB_FOLD) clean
		make -C $(MLX_FOLD) clean

fclean	: clean
		rm -rf $(NAME)
		rm -rf $(LIB_FOLD)$(LIB)
		rm -rf $(MLX_FOLD)$(MLX)

re		: fclean all