SRCS=$(addprefix ./srcs/, \
		$(addsuffix .c, \
			0_main 1_Init 2_Utils 3_Set_meshes 4_Drawing 5_Rendering 6_Rotation 7_Zoom 8_Handle_Keypress\
		)\
	)
OBJ=$(SRCS:%.c=%.o)
HEADER=./srcs/fdf.h
NAME=fdf

LIB=libft.a
LIB_FOLD=./libft/

CCFLAGS=-Wall -Werror -Wextra
IFLAGS=-I./minilibx-linux -I./libft/includes
LFLAGS=-L./minilibx-linux -L./libft -lmlx -lXext -lX11 -lft -lm

#-------------------------------------------

all 	: $(LIB) $(NAME)

$(LIB)	:
		make -C $(LIB_FOLD) all

$(NAME)	: $(LIB) $(OBJ)
		$(CC) $(CCFLAGS) $(IFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

%.o		: %.c $(HEADER)
		$(CC) $(CCFLAGS) $(IFLAGS) -c $< -o $@

clean	:
		rm -rf $(OBJ)
		make -C $(LIB_FOLD) clean

fclean	: clean
		rm -rf $(NAME)

re		: fclean all