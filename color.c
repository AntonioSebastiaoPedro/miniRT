/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 18:39:34 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(double r, double g, double b)
{
	t_color	c;

	c.e[0] = r;
	c.e[1] = g;
	c.e[2] = b;
	return (c);
}

bool	hit_sphere(t_vec3 center, double radius, t_ray r)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(center, r.orig);
	a = vec3_dot(r.dir, r.dir);
	b = -2.0 * vec3_dot(r.dir, oc);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

t_color	ray_color(const t_ray *r)
{
	t_vec3	unit_direction;

	if (hit_sphere(vec3(0, 0, -1), 0.5, *r))
	{
		return (color(1.0, 0.0, 0.0));
	}
	unit_direction = unit_vector(r->dir);
	double a = 0.5 * (vec3_y(&unit_direction) + 1.0); // Direção y normalizada
	return (vec3_add(vec3_scalar_mul(color(1.0, 1.0, 1.0), (1.0 - a)),
			vec3_scalar_mul(color(0.5, 0.7, 1.0), a)));
}

void	write_color(int fd, t_color pixel_color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * vec3_x(&pixel_color));
	g = (int)(255.999 * vec3_y(&pixel_color));
	b = (int)(255.999 * vec3_z(&pixel_color));
	dprintf(fd, "%d %d %d\n", r, g, b);
}
