/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:30:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/31 17:03:24 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	vec3_zero(void)
{
	return (vec3(0.0, 0.0, 0.0));
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3(-v.x, -v.y, -v.z));
}

t_vec3	vec3_add(t_vec3 u, t_vec3 v)
{
	return (vec3(u.x + v.x, u.y + v.y, u.z + v.z));
}

t_vec3	vec3_sub(t_vec3 u, t_vec3 v)
{
	return (vec3(u.x - v.x, u.y - v.y, u.z - v.z));
}

t_vec3	vec3_mul(t_vec3 u, t_vec3 v)
{
	return (vec3(u.x * v.x, u.y * v.y, u.z * v.z));
}

t_vec3	vec3_scalar_mul(t_vec3 v, double t)
{
	return (vec3(v.x * t, v.y * t, v.z * t));
}

t_vec3	vec3_scalar_div(t_vec3 v, double t)
{
	return (vec3_scalar_mul(v, 1.0 / t));
}

double	vec3_dot(t_vec3 u, t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	return (vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y
			* v.x));
}

t_vec3	vec3_unit(t_vec3 v)
{
	double	length;

	length = vec3_length(v);
	if (length == 0.0)
		return (vec3_zero());
	return (vec3_scalar_div(v, length));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
