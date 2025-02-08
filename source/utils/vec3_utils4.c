/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:28:43 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/08 18:24:38 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

double	vec3_distance(t_vec3 u, t_vec3 v)
{
	t_vec3	result;

	result = vec3_sub(u, v);
	return (vec3_length(result));
}
