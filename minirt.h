/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 18:48:23 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "color.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	check_file(char *path_file);
int		len_line_file(char *path_file);

#endif