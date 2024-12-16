# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/12/16 22:19:38 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = main.c get_next_line.c get_next_line_utils.c my_split.c parsing_color.c parsing_map.c  parsing_texture.c parsing_utils.c parsing_utils_2.c \
		minimap.c map.c player_move.c raycasting.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

build:
	@cd MLX42 && cmake -B build && cmake --build build -j4 
	
$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) -framework Cocoa -framework OpenGL -framework IOKit ./MLX42/build/libmlx42.a  $(OBJ) $(LIBFT) -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"  -o $(NAME)

%.o: %.c 
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all
