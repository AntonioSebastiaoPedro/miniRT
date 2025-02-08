/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:03:26 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/08 15:20:50 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	clamp_color(t_color color)
{
	color.x = fmin(fmax(color.x, 0.0), 255.0);
	color.y = fmin(fmax(color.y, 0.0), 255.0);
	color.z = fmin(fmax(color.z, 0.0), 255.0);
	return (color);
}

t_color	color(double r, double g, double b)
{
	t_color	c;

	c.x = r;
	c.y = g;
	c.z = b;
	return (c);
}

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	color = clamp_color(vec3(color.x / 255, color.y / 255, color.z / 255));
	r = (int)(color.x);
	g = (int)(color.y);
	b = (int)(color.z);
	return (r << 16 | g << 8 | b);
}

double	get_attenuation(t_scene scene, t_hit hit)
{
	double	distance;
	double	attenuation;
	double	kc;
	double	kl;
	double	kq;

	kc = 1.0;
	kl = 0.001;
	kq = 0.0009;
	distance = vec3_length(vec3_sub(scene.light.position, hit.hit_point));
	attenuation = scene.light.brightness / (kc + kl * distance + kq * distance
			* distance);
	return (attenuation);
}
