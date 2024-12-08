# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 17:08:07 by saharchi          #+#    #+#              #
#    Updated: 2024/12/08 21:00:23 by saharchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c get_next_line.c get_next_line_utils.c 

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(LIBFT): ./libft/*.c ./libft/libft.h 
	make -C ./libft/

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c 
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/bultins
	mkdir -p $(OBJDIR)/parsing
	mkdir -p $(OBJDIR)/execution

clean:
	$(RM) $(OBJ)
	make -C ./libft/ clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft/ fclean

re: fclean all