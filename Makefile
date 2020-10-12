

INC=/usr/local/include

INCLIB=$(INC)/../lib

CC=gcc

CFLAGS= -I$(INC) -O3 -I..

LFLAGS= -lmlx -lXext -lX11 -lm -lbsd

NAME= ./cub3D

SRC =	./src/main.c \
		./src/ft_control.c \
		./src/ft_coor.c \
		./src/ft_display.c \
		./src/ft_images.c \
		./src/ft_map.c \
		./src/ft_parsing.c \
		./src/ft_ray.c \
		./src/ft_utils.c \
		./Gnl/get_next_line_utils.c \
		./Gnl/get_next_line.c \
		./Libft/ft_atoi.c \

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(SRC) -D BUFFER_SIZE=32 $(LFLAGS)

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core

re	: clean all
