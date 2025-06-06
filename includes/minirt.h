/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:57:49 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/08 15:12:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_WIDTH 960
# define WIN_HEIGHT 540
# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CAMERA 3
# define LIGHT 4
# define PI 3.1415926535897932385
# define PROGRESS_COLOR 0x00FF00
# define BG_COLOR 0x444444
# define BAR_HEIGHT 20
# define BAR_START_X 50

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
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

typedef struct s_cyl_disks
{
	double			t_bottom;
	double			t_top;
	double			closest_t;
	double			t_side;
}					t_cyl_t;

typedef struct s_token
{
	char			**tokens;
	char			*token;
	char			*line;
	int				fd;

}					t_token;

t_color				ray_color(t_ray *r, t_hittable **objects, t_scene *scene);
t_color				color(double r, double g, double b);
void				viewport_init(t_viewport *viewport, t_camera *camera);
void				camera_init(t_camera *camera, t_viewport *viewport);
void				render_image(t_scene *scene, bool progress_bar);
void				reset_render(t_scene *scene);
void				update_render(t_scene *scene);
bool				hit_plane(void *object, t_ray *ray, t_hit *hit);
t_plane				*create_plane(t_plane plane_temp);
t_cylinder			*create_cylinder(t_cylinder cylinder_temp);
bool				hit_cylinder(void *data, t_ray *ray, t_ray_bounds *bounds,
						t_hit *hit);
void				init_scene(t_scene *scene);
void				set_hit_object(t_hit *hit, double t, t_vec3 hit_point,
						void *object);
int					color_to_int(t_color color);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int					ft_close(t_scene *scene);
t_vec3				set_normal(t_cylinder *cyl, t_hit *hit, t_cyl_t disk);
bool				is_valid_cylinder_height(t_cylinder *cyl, t_ray *ray,
						double t);
void				solve_equation_cy(t_quadratic_equation *eq, t_ray *ray,
						t_cylinder *cyl);
t_ray				create_ray_from_mouse(int x, int y, t_camera *camera);
void				rotate_object(int keycode, t_scene *scene);
void				resize(int keycode, t_scene *scene);
void				translate_object(int keycode, t_scene *scene);
void				draw_progress_bar(t_scene *scene, int current_scanline,
						int total_scanlines, t_img *img);
double				get_attenuation(t_scene scene, t_hit hit);

// Functions of parsing
int					has_rt_extension(char *file);
int					ft_strisspace(const char *str);
void				print_error(char *error_message, char *param);
void				parse_file(char *file, t_scene *scene);
void				parse_ambient_light(t_token t, t_scene *scene);
void				parse_light(t_token t, t_scene *scene);
void				free_split(char **tokens);
void				validate_token_number(char **tokens, int expec_count,
						t_token t, t_scene *scene);
void				init_a_c_l(t_scene *scene);
void				parse_camera(t_token t, t_scene *scene);
void				free_line_exit(char *line_current, int fd, t_scene *scene);
void				print_error_camera(char **tokens, t_token t, int is_dvs,
						t_scene *scene);
void				parse_sphere(t_token t, t_scene *scene);
void				print_error_plane(char **tokens, t_token t, int is_range,
						t_scene *scene);
void				print_error_cylinder(char **tokens, t_token t, int is_range,
						t_scene *scene);
void				parse_plane(t_token t, t_scene *scene);
void				parse_cylinder(t_token t, t_scene *scene);
double				str_to_double(char *str, char **tks_value, t_token *t,
						t_scene *scene);
double				parse_ratio(char **tokens, t_token t, int is_ambient_light,
						t_scene *scene);
double				parse_diameter(char *token, t_token t, t_scene *scene);
t_color				parse_color(char **tokens, char *token, t_token t,
						t_scene *scene);
int					mouse_hook(int keycode, int x, int y, t_scene *scene);
int					ft_hand_hook(int keycode, t_scene *scene);
void				free_scene(t_scene *scene);
void				free_mlx_scene(t_scene *scene, int exit_status);

#endif