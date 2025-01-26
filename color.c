/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/26 01:31:32 by ansebast         ###   ########.fr       */
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

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_color object_color)
{
	t_color	final_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_vec3	light_dir;
	double	diff_intensity;
	double	attenuation;
	double	distance;

	ambient_color = vec3_scalar_mul(object_color,
			scene->ambient_light.intensity);
	ambient_color = vec3_mul(ambient_color, scene->ambient_light.color);
	final_color = vec3_add(ambient_color, vec3_zero());
	light_dir = vec3_unit(vec3_sub(scene->light.position, hit->hit_point));
	distance = vec3_length(vec3_sub(scene->light.position, hit->hit_point));
	attenuation = scene->light.brightness / (1.0 + 0.1 * distance + 0.01
			* distance * distance);
	diff_intensity = fmax(0.0, vec3_dot(light_dir, hit->normal)) * attenuation;
	diffuse_color = vec3_scalar_mul(object_color, diff_intensity
			* scene->light.brightness);
	diffuse_color = vec3_mul(scene->light.color, diffuse_color);
	final_color = vec3_add(final_color, diffuse_color);
	return (final_color);
}

t_color	ray_color(t_ray *r, t_hittable **list, t_scene *scene)
{
	t_hit		hit;
	t_sphere	*sphere;
	t_plane		*plane;
	t_color		final_color;
	t_color		cor;

	if (is_hit(list, r, create_bounds(0, __DBL_MAX__), &hit))
	{
		if (hit.type == 0)
		{
			sphere = (t_sphere *)hit.object;
			cor = sphere->color;
		}
		else if (hit.type == 1)
		{
			plane = (t_plane *)hit.object;
			cor = plane->color;
		}
		final_color = calculate_lighting(scene, &hit, cor);
		return (final_color);
	}
	return (vec3_scalar_mul(scene->ambient_light.color,
			scene->ambient_light.intensity));
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
