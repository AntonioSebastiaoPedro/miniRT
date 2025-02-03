/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:56:04 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:30 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_quadratic_equation	solve_equation_sp(t_sphere *sp, t_ray *ray)
{
	t_quadratic_equation	eq;
	t_vec3					oc;

	oc = vec3_sub(sp->center, ray->orig);
	eq.a = vec3_dot(ray->dir, ray->dir);
	eq.b = -2.0 * vec3_dot(ray->dir, oc);
	eq.c = vec3_dot(oc, oc) - sp->radius * sp->radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	return (eq);
}

bool	hit_sphere(void *data, t_ray *r, t_ray_bounds *ray, t_hit *hit)
{
	t_quadratic_equation	eq;
	t_sphere				*sphere;
	double					root;
	t_vec3					outward_normal;

	sphere = (t_sphere *)data;
	eq = solve_equation_sp(sphere, r);
	if (eq.discriminant < 1e-16)
		return (false);
	root = (-eq.b - sqrt(eq.discriminant)) / (2.0 * eq.a);
	if (!is_in_bounds(ray, root))
	{
		root = (-eq.b + sqrt(eq.discriminant)) / (2.0 * eq.a);
		if (!is_in_bounds(ray, root))
			return (false);
	}
	hit->t = root;
	hit->hit_point = ray_point(r, hit->t);
	hit->object = data;
	hit->type = SPHERE;
	outward_normal = vec3_scalar_div(vec3_sub(hit->hit_point, sphere->center),
			sphere->radius);
	set_face_normal(hit, r, outward_normal);
	return (true);
}

t_sphere	*create_sphere(t_sphere sphere_temp)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->center = sphere_temp.center;
	sphere->color = sphere_temp.color;
	sphere->radius = sphere_temp.radius;
	return (sphere);
}

void	set_face_normal(t_hit *hit, t_ray *r, t_vec3 outward_normal)
{
	outward_normal = vec3_unit(outward_normal);
	hit->normal = outward_normal;
	hit->front_face = vec3_dot(r->dir, outward_normal) < 1e-16;
	if (hit->front_face == false)
		hit->normal = vec3_neg(outward_normal);
}
