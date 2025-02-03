/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:52:03 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:53:24 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_plane	*create_plane(t_plane plane_temp)
{
	t_plane	*plane;

	plane = (malloc(sizeof(t_plane)));
	plane->point = plane_temp.point;
	plane->normal = plane_temp.normal;
	plane->color = plane_temp.color;
	return (plane);
}

bool	hit_plane(void *object, t_ray *ray, t_hit *hit)
{
	t_plane	*plane;
	double	a;
	double	t;

	plane = (t_plane *)object;
	a = vec3_dot(ray->dir, plane->normal);
	if (fabs(a) < 1e-4)
		return (false);
	t = vec3_dot(vec3_sub(plane->point, ray->orig), plane->normal) / a;
	if (t < 1e-4)
		return (false);
	hit->normal = plane->normal;
	hit->object = plane;
	hit->t = t;
	hit->type = PLANE;
	hit->hit_point = vec3_add(ray->orig, vec3_scalar_mul(ray->dir, t));
	return (true);
}
