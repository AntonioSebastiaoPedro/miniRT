/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/17 18:36:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PI 3.1415926535897932385

# include "color.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "ray.h"
# include "vec3.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_camara
{
	int		image_width;
	int		image_height;
	int		max_depth;
	double	aspect_ratio;
	t_vec3	center;
	t_vec3	pixel00_loc;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
}			t_camara;

typedef struct s_viewport
{
	double	height;
	double	width;
	t_vec3	horizont;
	t_vec3	vertical;
	t_vec3	upper_left;
}			t_viewport;

// typedef struct s_material
// {
	
// }

inline int	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}
void		check_file(char *path_file);
int			len_line_file(char *path_file);
void		viewport_init(t_viewport *viewport, t_camara *camara);
void		camara_init(t_camara *camara, t_viewport *viewport);
void		render_image(t_camara *camara, t_hittable_list *list);
double		random_double(double min, double max);
double		linear_to_gama(double linear_component);
double		clamp(double value, double min, double max);

#endif