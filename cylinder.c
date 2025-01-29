/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:22:25 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/29 11:34:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_vec3 center, t_vec3 normal, t_color color,
		double diameter, double height)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->center = center;
	cylinder->normal = vec3_unit(normal);
	cylinder->color = color;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->radius = diameter / 2.0;
	return (cylinder);
}

bool	hit_cylinder(void *data, t_ray *ray, t_ray_bounds *bounds, t_hit *hit)
{
	t_quadratic_equation	eq;
	t_vec3					oc;
	t_vec3					ray_dir_normal;
	t_cylinder				*cylinder;
	double					t;
	double					t1;
	double					t2;
	double					cy_axis;
	t_vec3					outward_normal;

	cylinder = (t_cylinder *)data;
	oc = vec3_sub(ray->orig, cylinder->center);
	oc = vec3_sub(oc, vec3_scalar_mul(cylinder->normal, vec3_dot(oc,
					cylinder->normal)));
	ray_dir_normal = vec3_sub(ray->dir, vec3_scalar_mul(cylinder->normal,
				vec3_dot(ray->dir, cylinder->normal)));
	eq.a = vec3_dot(ray_dir_normal, ray_dir_normal);
	eq.b = 2.0 * vec3_dot(ray_dir_normal, oc);
	eq.c = vec3_dot(oc, oc) - pow(cylinder->radius, 2.0);
	eq.discriminant = eq.b * eq.b - 4.0 * eq.a * eq.c;
	if (eq.discriminant < 1e-6)
		return (false);
	t1 = (-eq.b - sqrt(eq.discriminant)) / (2.0 * eq.a);
	t2 = (-eq.b + sqrt(eq.discriminant)) / (2.0 * eq.a);
	if (!is_in_bounds(bounds, t1) && !is_in_bounds(bounds, t2))
		return (false);
	if (!is_in_bounds(bounds, t1))
		t = t2;
	else if (!is_in_bounds(bounds, t2))
		t = t1;
	else
		t = fmin(t1, t2);
	hit->hit_point = ray_point(ray, t);
	cy_axis = vec3_dot(vec3_sub(hit->hit_point, cylinder->center),
			cylinder->normal);
	if (cy_axis < 1e-16 || cy_axis > cylinder->height)
	{
		if (t == t1)
			t = t2;
		else
			t = t1;
		hit->hit_point = ray_point(ray, t);
		cy_axis = vec3_dot(vec3_sub(hit->hit_point, cylinder->center),
				cylinder->normal);
		if (cy_axis < 1e-16 || cy_axis > cylinder->height)
			return (false);
	}
	hit->t = t;
	hit->object = data;
	hit->type = 2;
	outward_normal = vec3_sub(hit->hit_point, vec3_add(cylinder->center,
					vec3_scalar_mul(cylinder->normal, cy_axis)));
	set_face_normal(hit, ray, outward_normal);
	return (true);
}
