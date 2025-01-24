/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:56:04 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/24 16:11:28 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(void *data, t_ray *r, t_ray_bounds *ray, t_hit *hit)
{
	t_quadratic_equation	eq;
	t_vec3					oc;
	t_sphere				*sphere;
	double					root;
	t_vec3					outword_normal;

	sphere = (t_sphere *)data;
	oc = vec3_sub(sphere->center, r->orig);
	eq.a = vec3_dot(r->dir, r->dir);
	eq.b = -2.0 * vec3_dot(r->dir, oc);
	eq.c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (false);
	root = (-eq.b - sqrt(eq.discriminant)) / (2.0 * eq.a);
	if (!is_in_bounds(ray, root))
	{
		root = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
		if (!is_in_bounds(ray, root))
			return (false);
	}
	hit->t = root;
	hit->hit_point = ray_point(r, hit->t);
	hit->object = data;
	outword_normal = vec3_scalar_div(vec3_sub(hit->hit_point, sphere->center),
			sphere->radius);
	set_face_normal(hit, r, outword_normal);
	return (true);
}

t_sphere	*create_sphere(t_vec3 center, t_color color, double radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->center = center;
	sphere->color = color;
	sphere->radius = fmax(0.0, radius);
	return (sphere);
}

void	set_face_normal(t_hit *hit, t_ray *r, t_vec3 outward_normal)
{
	outward_normal = vec3_unit(outward_normal);
	hit->normal = outward_normal;
	hit->front_face = vec3_dot(r->dir, outward_normal) < 0;
	if (hit->front_face == false)
		hit->normal = vec3_neg(outward_normal);
}
