/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:06:20 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:27 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3	ray_point(t_ray *r, double t)
{
	return (vec3_add(r->orig, vec3_scalar_mul(r->dir, t)));
}

t_ray	ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = vec3_unit(direction);
	return (r);
}

t_ray_bounds	create_bounds(double min, double max)
{
	t_ray_bounds	bounds;

	bounds.t_min = min;
	bounds.t_max = max;
	return (bounds);
}

bool	is_in_bounds(t_ray_bounds *ray_bounds, double value)
{
	if (value <= ray_bounds->t_min || value >= ray_bounds->t_max)
		return (false);
	return (true);
}

t_ray	create_ray_from_mouse(int x, int y, t_camera *camera)
{
	t_color	pixel_pos;
	t_vec3	ray_dir;
	t_ray	r;

	pixel_pos = vec3_add(vec3_add(camera->pixel00_loc,
				vec3_scalar_mul(camera->pixel_delta_u, x)),
			vec3_scalar_mul(camera->pixel_delta_v, y));
	ray_dir = vec3_unit(vec3_sub(pixel_pos, camera->center));
	r = ray(camera->center, ray_dir);
	return (r);
}
