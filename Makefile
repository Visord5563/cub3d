# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: relamine <relamine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2025/01/31 23:24:15 by relamine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast
RM = rm -f

SRC = main.c get_next_line.c get_next_line_utils.c my_split.c parsing_color.c parsing_map.c  parsing_texture.c parsing_utils.c init_function.c \
		minimap.c map.c player_move.c raycasting.c texture.c color_utils.c player_move_utils.c minimap_render.c parsing.c free_function.c mouse.c \
		raycasting_utils.c get_ray.c utils.c \

OBJ = $(SRC:%.c=%.o)
LIBMLX := ../MLX42
LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(NAME)

	
$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) -framework Cocoa -framework OpenGL -framework IOKit $(LIBS)  $(OBJ) $(LIBFT) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"  -o $(NAME)

%.o: %.c  ./cub3d.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all
