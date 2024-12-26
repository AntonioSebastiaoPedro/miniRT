# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 00:51:16 by ansebast          #+#    #+#              #
#    Updated: 2024/12/26 14:53:07 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror -g
LIBSRC = ./libft
MLXSRC = ./minilibx
LIBFT = $(LIBSRC)/libft.a
MLX = $(MLXSRC)/libmlx.a
SRC = main.c validation_file.c
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

.PHONY: all clean fclean re