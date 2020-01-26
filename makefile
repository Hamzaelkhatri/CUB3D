# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 19:24:16 by helkhatr          #+#    #+#              #
#    Updated: 2020/01/25 19:25:00 by helkhatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX = -lmlx -lm -framework OpenGL -framework AppKit
CFLAGE =  -Wall -Wextra -Werror
NAME = cub3D

SRCS = src/cub3d.c					\
	  src/bitmap.c					\
	  src/calcule_values.c			\
	  src/check_map.c 				\
	  src/dr_sprite.c 				\
	  src/draw.c 					\
	  src/floor_ceil.c				\
	  src/ft_atoi.c 				\
	  src/ft_func.c 				\
	  src/ft_lib.c 					\
	  src/get_map.c 				\
	  src/get_next_line_utils.c 	\
	  src/get_next_line.c 			\
	  src/get_position.c 			\
	  src/get_sprites.c 			\
	  src/image.c 					\
	  src/init.c 					\
	  src/parse_main.c 				\
	  src/player_seconde.c 			\
	  src/player.c 					\
	  src/raycast.c 				\
	  src/realisation.c 			\
	  src/sprites.c 				\
	  src/window_config.c			\
	  src/positiontexture.c


OBJ = $(SRCS:.c=.o)

$(NAME) : $(OBJ)
	@rm -rf Cub3D
	@gcc $(OBJ) -I./includes -I./usr/include $(CFLAGE) $(MLX) -o $(NAME)
	@echo "[Done !]"

all : $(NAME)

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
