# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 11:32:47 by ansebast          #+#    #+#              #
#    Updated: 2025/01/29 20:46:45 by ansebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m

BONUS_SRC = 

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
      ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isnumber.c\
      ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
      ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
      ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
      ft_strisspace.c ft_strcmp.c ft_strtod.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	ft_freearray.c ft_abs.c ft_freematrix.c ft_lstmap.c ft_lstnew.c \
	ft_lstsize.c get_next_line.c ft_atoi_base.c ft_puterror.c ft_strtok.c ft_strtol.c \

BONUS_OBJS = $(BONUS_SRC:.c=.o)

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CYAN)Creating the library $(NAME)...$(RESET)"
	ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Library $(NAME) successfully created!$(RESET)"

bonus: $(OBJS) $(BONUS_OBJS)
	@echo "$(CYAN)Adding bonus files...$(RESET)"
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)Bonus files added successfully!$(RESET)"

clean:
	@echo "$(RED)Removing all object files...$(RESET)"
	rm -f $(OBJS) $(BONUS_OBJS) libft.so
	
fclean: clean
	@echo "$(RED)Removing the library $(NAME)...$(RESET)"
	rm -f $(NAME)
	@echo "$(GREEN)Library $(NAME) successfully removed!$(RESET)"

re: fclean all

rebonus: re bonus

.PHONY: all clean fclean re bonus