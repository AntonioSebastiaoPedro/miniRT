/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/26 14:46:28 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	check_file(char *path_file);
int		len_line_file(char *path_file);

#endif