/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:04:05 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 08:01:26 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "vec3.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_vec3	t_color;
typedef struct s_ray
{
	struct s_vec3		orig;
	struct s_vec3		dir;
}						t_ray;

typedef struct s_hit
{
	struct s_vec3		hit_point;
	struct s_vec3		normal;
	void				*object;
	int					type;
	double				t;
	bool				front_face;
}						t_hit;

typedef struct s_quadratic_equation
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
}						t_quadratic_equation;

typedef struct s_hittable
{
	void				*data;
	int					type;
	struct s_hittable	*next;
}						t_hittable;

typedef struct s_sphere
{
	struct s_vec3		center;
	t_color				color;
	double				radius;
	double				diameter;
}						t_sphere;

typedef struct s_ray_bounds
{
	double				t_min;
	double				t_max;
}						t_ray_bounds;

void					set_face_normal(t_hit *hit, t_ray *r,
							t_vec3 outward_normal);
bool					hit_sphere(void *object, t_ray *r,
							t_ray_bounds *ray_bounds, t_hit *hit);
t_sphere				*create_sphere(t_sphere sphere_temp);
t_ray					ray(t_vec3 origin, t_vec3 direction);
t_vec3					ray_point(t_ray *r, double t);
bool					is_hit(t_hittable **objects, t_ray *r,
							t_ray_bounds *ray_bounds, t_hit *hit);
bool					is_in_bounds(t_ray_bounds *ray_bounds, double value);
t_ray_bounds			create_bounds(double min, double max);
t_hittable				*hittable_new(int type, void *data);
void					hittable_add_back(t_hittable **lst, t_hittable *new);
t_hittable				*hittable_last(t_hittable *objects);
void					add_to_hittable_list(t_hittable **list, int type,
							void *data);

#endif
