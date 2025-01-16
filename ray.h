/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:04:05 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/16 12:35:27 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "vec3.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_ray
{
	struct s_vec3	orig;
	struct s_vec3	dir;
}					t_ray;

typedef struct s_hit
{
	struct s_vec3	hit_point;
	struct s_vec3	normal;
	double			t;
	bool			front_face;
}					t_hit;

typedef struct s_quadratic_equation
{
	double			a;
	double			b;
	double			c;
	double			discriminant;
}					t_quadratic_equation;

typedef struct s_hittable
{
	void			*data;
}					t_hittable;

typedef struct s_hittable_list
{
	t_hittable		**objects;
	size_t			size;
	size_t			capacity;
}					t_hittable_list;

typedef struct s_sphere
{
	struct s_vec3	center;
	double			radius;
}					t_sphere;

typedef struct s_ray_bounds
{
	double			t_min;
	double			t_max;
}					t_ray_bounds;

void				set_face_normal(t_hit *hit, t_ray *r,
						t_vec3 outward_normal);
bool				hit_sphere(t_hittable *hittable, t_ray *r,
						t_ray_bounds *ray_bounds, t_hit *hit);
t_hittable			*create_sphere(t_vec3 center, double radius);
t_ray				ray(t_vec3 origin, t_vec3 direction);
t_vec3				ray_point(t_ray *r, double t);
bool				is_hit(t_hittable_list *list, t_ray *r,
						t_ray_bounds *ray_bounds, t_hit *hit);
void				add_hittable(t_hittable_list *list, t_hittable *object);
t_hittable_list		create_hittable_list(size_t initial_capacity);
bool				is_in_bounds(t_ray_bounds *ray_bounds, double value);
t_ray_bounds		*create_bounds(double min, double max);

#endif
