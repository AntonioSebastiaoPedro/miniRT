/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 14:57:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	shadow_test(t_scene *scene, t_hittable **list, t_hit *hit)
{
	t_ray_bounds	limits;
	double			light_distance;
	t_vec3			light_dir;
	t_ray			shadow_ray;

	light_dir = vec3_unit(vec3_sub(scene->light.position, hit->hit_point));
	light_distance = vec3_length(vec3_sub(scene->light.position,
				hit->hit_point));
	shadow_ray.orig = vec3_add(hit->hit_point,
			vec3_scalar_mul(scene->light.position, 1e-6));
	shadow_ray.dir = light_dir;
	limits = create_bounds(1e-6, light_distance);
	if (is_hit(list, &shadow_ray, &limits, hit))
		return (true);
	return (false);
}

t_color	get_ambient_color(t_color object_color, t_scene *scene)
{
	t_color	ambient_color;

	ambient_color = vec3_scalar_mul(object_color,
			scene->ambient_light.intensity);
	ambient_color = vec3_mul(ambient_color, scene->ambient_light.color);
	return (ambient_color);
}

t_color	calculate_lighting(t_scene *scene, t_hit *hit, t_color object_color,
		t_hittable **list)
{
	t_color	final_color;
	t_color	diffuse_color;
	t_vec3	light_dir;
	t_vec3	new_normal;
	double	diff_intensity;

	final_color = get_ambient_color(object_color, scene);
	if (!shadow_test(scene, list, hit))
	{
		light_dir = vec3_unit(vec3_sub(scene->light.position, hit->hit_point));
		new_normal = hit->normal;
		if (vec3_dot(light_dir, new_normal) < 1e-64)
			new_normal = vec3_neg(new_normal);
		diff_intensity = fmax(0.0, vec3_dot(light_dir, new_normal));
		diffuse_color = vec3_scalar_mul(object_color, diff_intensity
				* scene->light.brightness);
		diffuse_color = vec3_mul(scene->light.color, diffuse_color);
		final_color = vec3_add(final_color, diffuse_color);
	}
	return (final_color);
}

t_color	get_object_color(t_hit *hit)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (hit->type == SPHERE)
	{
		sphere = (t_sphere *)hit->object;
		return (sphere->color);
	}
	else if (hit->type == PLANE)
	{
		plane = (t_plane *)hit->object;
		return (plane->color);
	}
	else if (hit->type == CYLINDER)
	{
		cylinder = (t_cylinder *)hit->object;
		return (cylinder->color);
	}
	return (vec3_zero());
}

t_color	ray_color(t_ray *r, t_hittable **list, t_scene *scene)
{
	t_ray_bounds	limits;
	t_hit			hit;
	t_color			final_color;
	t_color			color;

	limits = create_bounds(1e-16, __DBL_MAX__);
	if (is_hit(list, r, &limits, &hit))
	{
		color = get_object_color(&hit);
		final_color = calculate_lighting(scene, &hit, color, list);
		return (final_color);
	}
	return (vec3_cross(vec3_scalar_mul(scene->ambient_light.color,
				scene->ambient_light.intensity), vec3_zero()));
}
