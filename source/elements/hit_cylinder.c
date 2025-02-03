/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:54:26 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:18 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	find_roots(t_quadratic_equation eq, double *t1, double *t2)
{
	*t1 = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	*t2 = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
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
