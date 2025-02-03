/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:22:25 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:15 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_cylinder	*create_cylinder(t_cylinder cylinder_temp)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->center = cylinder_temp.center;
	cylinder->normal = vec3_unit(cylinder_temp.normal);
	cylinder->color = cylinder_temp.color;
	cylinder->diameter = cylinder_temp.diameter;
	cylinder->height = cylinder_temp.height;
	cylinder->radius = cylinder_temp.diameter / 2.0;
	return (cylinder);
}

bool	is_valid_cylinder_height(t_cylinder *cyl, t_ray *ray, double t)
{
	t_vec3	point;
	double	projection;

	point = ray_point(ray, t);
	projection = vec3_dot(vec3_sub(point, cyl->center), cyl->normal);
	return (projection >= 0 && projection <= cyl->height);
}

void	solve_equation_cy(t_quadratic_equation *eq, t_ray *ray, t_cylinder *cyl)
{
	t_vec3	oc;

	oc = vec3_sub(ray->orig, cyl->center);
	eq->a = vec3_dot(ray->dir, ray->dir) - pow(vec3_dot(ray->dir, cyl->normal),
			2);
	eq->b = 2 * (vec3_dot(ray->dir, oc) - vec3_dot(ray->dir, cyl->normal)
			* vec3_dot(oc, cyl->normal));
	eq->c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cyl->normal), 2)
		- pow(cyl->radius, 2);
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
}

t_vec3	set_normal(t_cylinder *cyl, t_hit *hit, t_cyl_t disk)
{
	t_vec3	normal;
	t_vec3	closest_point;

	if (disk.closest_t == disk.t_bottom)
		normal = vec3_scalar_mul(cyl->normal, -1);
	else if (disk.closest_t == disk.t_top)
		normal = cyl->normal;
	else
	{
		closest_point = vec3_add(cyl->center, vec3_scalar_mul(cyl->normal,
					vec3_dot(vec3_sub(hit->hit_point, cyl->center),
						cyl->normal)));
		normal = vec3_unit(vec3_sub(hit->hit_point, closest_point));
	}
	return (normal);
}
