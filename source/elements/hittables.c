/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:35:12 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:21 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	update_closest_object(double *closest, bool *hit_anything, t_hit *hit,
		t_hit hit_temp)
{
	if (hit_temp.t < *closest)
	{
		*hit = hit_temp;
		*hit_anything = true;
		*closest = hit_temp.t;
	}
}

bool	is_hit(t_hittable **list, t_ray *r, t_ray_bounds *bounds, t_hit *hit)
{
	t_hit			hit_temp;
	bool			hit_anything;
	double			closest;
	t_hittable		*curr;
	t_ray_bounds	limits;

	closest = bounds->t_max;
	hit_anything = false;
	curr = (*list);
	while (curr)
	{
		limits = create_bounds(bounds->t_min, closest);
		if (curr->type == SPHERE)
			if (hit_sphere(curr->data, r, &limits, &hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		if (curr->type == PLANE)
			if (hit_plane(curr->data, r, &hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		if (curr->type == CYLINDER)
			if (hit_cylinder(curr->data, r, &limits, &hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		curr = curr->next;
	}
	return (hit_anything);
}
