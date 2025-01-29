/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/29 18:32:27 by ansebast         ###   ########.fr       */
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

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.x / 255);
	g = (int)(color.y / 255);
	b = (int)(color.z / 255);
	return (r << 16 | g << 8 | b);
}

bool	shadow_test(t_scene *scene, t_hittable **list, t_hit *hit)
{
	double	light_distance;
	t_vec3	light_dir;
	t_ray	shadow_ray;

	light_dir = vec3_unit(vec3_sub(scene->light.position, hit->hit_point));
	light_distance = vec3_length(vec3_sub(scene->light.position,
				hit->hit_point));
	shadow_ray.orig = vec3_add(hit->hit_point,
			vec3_scalar_mul(scene->light.position, 1e-6));
	shadow_ray.dir = light_dir;
	if (is_hit(list, &shadow_ray, create_bounds(1e-6, light_distance), hit))
		return (true);
	return (false);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_color object_color,
		t_hittable **list)
{
	t_color	final_color;
	t_color	diffuse_color;
	t_color	ambient_color;
	t_vec3	light_dir;
	double	diff_intensity;

	ambient_color = vec3_scalar_mul(object_color,
			scene->ambient_light.intensity);
	ambient_color = vec3_mul(ambient_color, scene->ambient_light.color);
	final_color = ambient_color;
	if (!shadow_test(scene, list, hit))
	{
		light_dir = vec3_unit(vec3_sub(scene->light.position, hit->hit_point));
		diff_intensity = fmax(0.0, vec3_dot(light_dir, hit->normal));
		diffuse_color = vec3_scalar_mul(object_color, diff_intensity
				* scene->light.brightness);
		diffuse_color = vec3_mul(scene->light.color, diffuse_color);
		final_color = vec3_add(final_color, diffuse_color);
	}
	return (final_color);
}

t_color	ray_color(t_ray *r, t_hittable **list, t_scene *scene)
{
	t_hit		hit;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_color		final_color;
	t_color		cor;

	if (is_hit(list, r, create_bounds(1e-16, __DBL_MAX__), &hit))
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
		else if (hit.type == 2)
		{
			cylinder = (t_cylinder *)hit.object;
			cor = cylinder->color;
		}
		final_color = calculate_lighting(scene, &hit, cor, list);
		return (final_color);
	}
	return (vec3_cross(vec3_scalar_mul(scene->ambient_light.color,
				scene->ambient_light.intensity), vec3_zero()));
}
