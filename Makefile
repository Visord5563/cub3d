# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/12/18 20:18:10 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -fsanitize=address -g
RM = rm -f

SRC = main.c get_next_line.c get_next_line_utils.c my_split.c parsing_color.c parsing_map.c  parsing_texture.c parsing_utils.c parsing_utils_2.c \
		minimap.c map.c player_move.c raycasting.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

build:
	@cd MLX42 && cmake -B build && cmake --build build -j4 
	
$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT) cub3d.h
	gcc $(CFLAGS) $(OBJ) $(LIBFT) ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm -o $(NAME)
%.o: %.c cub3d.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all
