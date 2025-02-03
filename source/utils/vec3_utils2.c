/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:26:08 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:49:46 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
