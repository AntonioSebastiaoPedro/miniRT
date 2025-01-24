/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/24 00:59:55 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(double r, double g, double b)
{
	t_color	c;

	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}

t_color	ray_color(t_ray *r, t_hittable **list)
{
	t_hit		hit;
	t_vec3		unit_direction;
	t_sphere	*sphere;
	double		a;

	if (is_hit(list, r, create_bounds(0, __DBL_MAX__), &hit))
	{
		sphere = (t_sphere *)hit.object;
		return (sphere->color);
	}
	unit_direction = vec3_unit(r->dir);
	a = 0.5 * (unit_direction.y + 1.0);
	return (vec3_add(vec3_scalar_mul(color(1.0, 1.0, 1.0), (1.0 - a)),
			vec3_scalar_mul(color(0.5, 0.7, 1.0), a)));
}

void	write_color(int fd, t_color pixel_color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * pixel_color.x);
	g = (int)(255.999 * pixel_color.y);
	b = (int)(255.999 * pixel_color.z);
	dprintf(fd, "%d %d %d\n", r, g, b);
}
