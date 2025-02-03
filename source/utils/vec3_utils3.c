/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:27:38 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:49:50 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	return (vec3(v.x, cos_angle * v.y - sin_angle * v.z, sin_angle * v.y
			+ cos_angle * v.z));
}

t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	return (vec3(cos_angle * v.x + sin_angle * v.z, v.y, -sin_angle * v.x
			+ cos_angle * v.z));
}

t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	return (vec3(cos_angle * v.x - sin_angle * v.y, sin_angle * v.x + cos_angle
			* v.y, v.z));
}
