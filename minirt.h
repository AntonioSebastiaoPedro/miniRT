/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 11:11:21 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 1920 / 2
# define WIN_HEIGHT 1080 / 2
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
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

typedef struct s_camera
{
	double			aspect_ratio;
	double			fov;
	double			focal_length;
	t_vec3			center;
	t_vec3			pixel00_loc;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	t_vec3			dvs;
	t_vec3			dh;
	t_vec3			dv;
	int				image_height;
	int				image_width;
}					t_camera;

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

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			normal;
	t_color			color;
	double			diameter;
	double			radius;
	double			height;

}					t_cylinder;
typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_light			light;
	t_camera		camera;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_img			img;
	t_viewport		viewport;
	t_hittable		*object_list;
	void			*mlx;
	void			*mlx_win;
	void			*selected_object;
	char			*map;
	int				num_light;
	int				num_camera;
	int				num_ambient_light;
	int				num_spheres;
	int				num_planes;
	int				num_cylinders;
	int				type_selected_object;
}					t_scene;

typedef struct s_file
{
	int				fd;
	char			*line;
}					t_file;

t_color				ray_color(t_ray *r, t_hittable **objects, t_scene *scene);
t_color				color(double r, double g, double b);
void				check_file(char *path_file);
int					len_line_file(char *path_file);
void				viewport_init(t_viewport *viewport, t_camera *camera);
void				camera_init(t_camera *camera, t_viewport *viewport);
void				render_image(t_camera *camera, t_hittable **objects,
						t_scene *scene, bool progress_bar);
bool				hit_plane(void *object, t_ray *ray, t_hit *hit);
t_plane				*create_plane(t_plane plane_temp);
t_cylinder			*create_cylinder(t_cylinder cylinder_temp);
bool				hit_cylinder(void *data, t_ray *ray, t_ray_bounds *bounds,
						t_hit *hit);
void				init_scene(t_scene *scene);
int					color_to_int(t_color color);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int					ft_close(t_scene *scene);

// Functions of parsing
int					has_rt_extension(char *file);
int					ft_strisspace(const char *str);
void				print_error(char *error_message, char *param);
void				parse_file(char *file, t_scene *scene);
void				parse_ambient_light(char *line, int fd, t_scene *scene);
void				parse_light(char *line, int fd, t_scene *scene);
void				free_split(char **tokens);
void				validate_token_number(char **tokens, int expec_count,
						char *line, int fd);
void				init_a_c_l(t_scene *scene);
void				parse_camera(char *line, int fd, t_scene *scene);
void				free_line_exit(char *line_current, int fd);
void				print_error_camera(char **tokens, char *line, int fd,
						int is_dvs);
void				parse_sphere(char *line, int fd, t_scene *scene);
void				print_error_plane(char **tokens, char *line, int fd,
						int is_range);
void				print_error_cylinder(char **tokens, char *line, int fd,
						int is_range);
void				parse_plane(char *line, int fd, t_scene *scene);
void				parse_cylinder(char *line, int fd, t_scene *scene);
double				str_to_double(char *str, char **tks_value, char **tokens,
						t_file *file);
double				parse_ratio(char **tokens, char *line, int fd,
						int is_ambient_light);
double				parse_diameter(char **tokens, char *token, char *line,
						int fd);
t_color				parse_color(char **tokens, char *token, char *line, int fd);
int					mouse_hook(int keycode, int x, int y, t_scene *scene);
int					ft_hand_hook(int keycode, t_scene *scene);
void				free_scene(t_scene *scene);

#endif