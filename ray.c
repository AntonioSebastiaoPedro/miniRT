/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:06:20 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/17 10:28:38 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ray_point(t_ray *r, double t)
{
	return (vec3_add(r->orig, vec3_scalar_mul(r->dir, t)));
}

t_ray	ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

t_ray_bounds *create_bounds(double min, double max)
{
	t_ray_bounds	*bounds;

	bounds = malloc(sizeof(t_ray_bounds));
	bounds->t_min = min;
	bounds->t_max = max;
	return (bounds);
}

bool	is_in_bounds(t_ray_bounds *ray_bounds, double value)
{
	if (value <= ray_bounds->t_min || value >= ray_bounds->t_max)
		return (false);
	return (true);
}
