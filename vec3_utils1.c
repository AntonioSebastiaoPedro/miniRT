/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:30:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 13:28:26 by ansebast         ###   ########.fr       */
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
