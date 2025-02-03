/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:22:25 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 13:42:33 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	hit_disk(t_cylinder *cyl, t_vec3 normal, t_ray *ray, t_ray_bounds *b)
{
	double	denom;
	double	t;
	t_vec3	p;
	double	distance;

	denom = vec3_dot(normal, ray->dir);
	if (fabs(denom) < 1e-6)
		return (INFINITY);
	t = vec3_dot(vec3_sub(cyl->center, ray->orig), normal) / denom;
	if (!is_in_bounds(b, t))
		return (INFINITY);
	p = ray_point(ray, t);
	distance = vec3_length(vec3_sub(p, cyl->center));
	if (distance <= cyl->radius)
		return (t);
	return (INFINITY);
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

void	find_roots(t_quadratic_equation eq, double *t1, double *t2)
{
	*t1 = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	*t2 = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
}

double	find_disk_t(t_cylinder *cyl, t_ray_bounds *bounds, t_ray *ray,
		t_vec3 normal)
{
	double	t;

	t = hit_disk(cyl, normal, ray, bounds);
	return (t);
}

t_cyl_t	find_closest_t(t_cylinder *cy, t_ray_bounds *bounds, double t_side,
		t_ray *ray)
{
	int		hits;
	int		i;
	double	t[3];
	t_cyl_t	disk;
	t_vec3	center;

	hits = 0;
	center = cy->center;
	disk.t_bottom = find_disk_t(cy, bounds, ray, vec3_scalar_mul(cy->normal,
				-1));
	cy->center = vec3_add(cy->center, vec3_scalar_mul(cy->normal, cy->height));
	disk.t_top = find_disk_t(cy, bounds, ray, cy->normal);
	cy->center = center;
	if (t_side < INFINITY)
		t[hits++] = t_side;
	if (disk.t_bottom < INFINITY)
		t[hits++] = disk.t_bottom;
	if (disk.t_top < INFINITY)
		t[hits++] = disk.t_top;
	disk.closest_t = INFINITY;
	i = -1;
	while (++i < hits)
		if (t[i] < disk.closest_t)
			disk.closest_t = t[i];
	return (disk);
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

bool	hit_cylinder(void *data, t_ray *ray, t_ray_bounds *bounds, t_hit *hit)
{
	t_quadratic_equation	eq;
	t_cylinder				*cyl;
	t_cyl_t					disk;
	double					t1;
	double					t2;

	cyl = (t_cylinder *)data;
	solve_equation_cy(&eq, ray, cyl);
	disk.t_side = INFINITY;
	if (eq.discriminant > 0)
	{
		find_roots(eq, &t1, &t2);
		if (is_in_bounds(bounds, t1) && is_valid_cylinder_height(cyl, ray, t1))
			disk.t_side = t1;
		if (is_in_bounds(bounds, t2) && is_valid_cylinder_height(cyl, ray, t2)
			&& t2 < disk.t_side)
			disk.t_side = t2;
	}
	disk = find_closest_t(cyl, bounds, disk.t_side, ray);
	if (disk.closest_t == INFINITY)
		return (false);
	set_hit_object(hit, disk.closest_t, ray_point(ray, disk.closest_t), data);
	hit->type = CYLINDER;
	set_face_normal(hit, ray, set_normal(cyl, hit, disk));
	return (true);
}
