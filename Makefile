INC=/usr/local/include

INCLIB=$(INC)/../lib
CC=gcc

	LFLAGS= -lmlx -lXext -lX11 -lm -lbsd -march=native -g3 -fsanitize=address

NAME= ./cub3D

SRC =	./src/main.c \
		./src/init.c \
		./src/extract_textures.c \
		./src/extract_textures2.c \
		./src/find_chars.c \
		./src/param_sprites.c \
		./src/param_enemy.c \
		./src/draw.c \
		./src/drawcol.c \
		./src/sprites.c \
		./src/doors_bonus.c \
		./src/ft_pythagore.c \
		./src/animation.c \
		./src/raymachine.c \
		./src/ft_ray_col.c \
		./src/events.c \
		./src/ft_control.c \
		./src/ft_control2.c \
		./src/ft_coor.c \
		./src/ft_display.c \
		./src/ft_images.c \
		./src/ft_save.c \
		./src/ft_map.c \
		./src/ft_map2.c \
		./src/find_info.c \
		./src/ft_parsing.c \
		./src/ft_ray.c \
		./src/ft_utils.c \
		./src/ft_clean.c \
		./src/ft_check.c \
		./src/Gnl/get_next_line_utils.c \
		./src/Gnl/get_next_line.c \
		./src/Libft/ft_atoi.c \
		./src/Libft/ft_strmcat.c \
		./src/Libft/ft_strlen.c \
		./src/Libft/ft_substr.c \
		./src/Libft/ft_ctostr.c \
		./src/Libft/ft_strncmp.c \
		./src/Libft/ft_strdup.c \
		./src/Libft/ft_putstr_fd.c \
		./src/Libft/ft_strrchr.c \

all	:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(SRC) libftprintf.a -D BUFFER_SIZE=32 $(LFLAGS)

clean	:
	rm -f $(NAME) $(OBJ) *~ core *.core

re	: clean all
