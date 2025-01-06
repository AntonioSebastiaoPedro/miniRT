/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:30:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 15:49:33 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(double e0, double e1, double e2)
{
	t_vec3	v;

	v.e[0] = e0;
	v.e[1] = e1;
	v.e[2] = e2;
	return (v);
}

t_vec3	vec3_zero(void)
{
	return (vec3(0, 0, 0));
}

double	vec3_x(t_vec3 *v)
{
	return (v->e[0]);
}

double	vec3_y(t_vec3 *v)
{
	return (v->e[1]);
}

double	vec3_z(t_vec3 *v)
{
	return (v->e[2]);
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3(-v.e[0], -v.e[1], -v.e[2]));
}

t_vec3	vec3_add(t_vec3 u, t_vec3 v)
{
	return (vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]));
}

t_vec3	vec3_sub(t_vec3 u, t_vec3 v)
{
	return (vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]));
}

t_vec3	vec3_mul(t_vec3 u, t_vec3 v)
{
	return (vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]));
}

t_vec3	vec3_scalar_mul(t_vec3 v, double t)
{
	return (vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t));
}

t_vec3	vec3_scalar_div(t_vec3 v, double t)
{
	return (vec3_scalar_mul(v, 1 / t));
}

double	vec3_dot(t_vec3 u, t_vec3 v)
{
	return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

t_vec3	vec3_cross(t_vec3 u, t_vec3 v)
{
	return (vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0]
			* v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]));
}

t_vec3	vec3_unit(t_vec3 v)
{
	return (vec3_scalar_div(v, vec3_length(v)));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

t_vec3	unit_vector(t_vec3 v)
{
	double length = vec3_length(v); // Calcula o comprimento do vetor
	if (length == 0)
	{
		// Evita divisão por zero
		return (vec3_zero());
	}
	return (vec3_scalar_div(v, length));
		// Divide cada componente pelo comprimento
}
