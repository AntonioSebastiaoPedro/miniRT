# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 00:51:16 by ansebast          #+#    #+#              #
#    Updated: 2025/02/03 19:00:50 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror -g
LIBSRC = ./libft
MLXSRC = ./minilibx
LIBFT = $(LIBSRC)/libft.a
MLX = $(MLXSRC)/libmlx.a
SRC = ./source/main.c ./source/elements/color.c ./source/elements/ray.c ./source/elements/hittables.c \
	./source/elements/sphere.c ./source/elements/camera.c ./source/elements/plane.c ./source/elements/cylinder.c \
	./source/utils/mlx_utils.c ./source/parse/parse_file.c ./source/hook_events.c ./source/utils/free_utils.c \
	./source/parse/parse_ambient_light.c ./source/parse/parse_camera.c ./source/parse/parse_light.c \
	./source/parse/parse_sphere.c ./source/parse/parse_plane.c ./source/parse/parse_cylinder.c \
       ./source/utils/parse_utils.c ./source/utils/tokens_utils.c ./source/utils/minirt_utils.c \
       ./source/utils/errors_utils.c ./source//utils/vec3_utils1.c ./source/utils/vec3_utils2.c \
       ./source/utils/vec3_utils3.c ./source/utils/vec3_utils4.c ./source/utils/hit_utils.c \
       ./source/elements/hit_cylinder.c ./source/utils/color_utils.c ./source/transformations/rotate.c \
       ./source/transformations/resize.c ./source/render.c ./source/transformations/translate.c
       
OBJS = $(SRC:.c=.o)

INCLUDES = -I$(LIBSRC) -I$(MLXSRC)

LIBRARIES = -L$(LIBSRC) -lft -L$(MLXSRC) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	cc $(CFLAGS) $(OBJS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

$(LIBFT):
	@make bonus -C $(LIBSRC)

$(MLX):
	@make -C $(MLXSRC)

clean:
	rm -f $(OBJS)
	@make clean -C $(LIBSRC)
	@make clean -C $(MLXSRC)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBSRC)

re: fclean all

run: all
	./miniRT

.PHONY: all clean fclean re