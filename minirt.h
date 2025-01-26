/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/25 21:49:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PI 3.1415926535897932385

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
	int				image_width;
	int				image_height;
	double			aspect_ratio;
	double			fov;
	double			focal_length;
	t_vec3			center;
	t_vec3			pixel00_loc;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	t_vec3			orientation;
}					t_camara;

typedef struct s_viewport
{
	double			height;
	double			width;
	t_vec3			horizont;
	t_vec3			vertical;
	t_vec3			upper_left;
	t_vec3			center;
}					t_viewport;

typedef struct s_light
{
	t_vec3			position;
	double			brightness;
	t_color			color;
}					t_light;
typedef t_vec3		t_color;

typedef struct s_ambient_light
{
	double			intensity;
	t_color			color;
}					t_ambient_light;

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_light			light;
}					t_scene;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_plane;

void				write_color(int fd, t_color pixel_color);
t_color				ray_color(t_ray *r, t_hittable **objects, t_scene *scene);
t_color				color(double r, double g, double b);
void				check_file(char *path_file);
int					len_line_file(char *path_file);
void				viewport_init(t_viewport *viewport, t_camara *camara);
void				camara_init(t_camara *camara, t_viewport *viewport);
void				render_image(t_camara *camara, t_hittable **objects,
						t_scene *scene);
bool				hit_plane(void *object, t_ray *ray, t_hit *hit);
t_plane				*create_plane(t_vec3 point, t_vec3 normal, t_color color);

#endif