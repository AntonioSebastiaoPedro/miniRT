/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:02:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 05:32:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_object(t_scene *scene, t_ray *ray)
{
	t_hit	hit_temp;

	if (is_hit(&scene->object_list, ray, create_bounds(1e-64, __DBL_MAX__),
			&hit_temp))
	{
		if (hit_temp.type == SPHERE)
		{
			scene->selected_object = (t_sphere *)hit_temp.object;
			scene->type_selected_object = SPHERE;
		}
		else if (hit_temp.type == PLANE)
		{
			scene->selected_object = (t_plane *)hit_temp.object;
			scene->type_selected_object = PLANE;
		}
		else if (hit_temp.type == CYLINDER)
		{
			scene->selected_object = (t_cylinder *)hit_temp.object;
			scene->type_selected_object = CYLINDER;
		}
	}
}

t_ray	create_ray_from_mouse(int x, int y, t_camera *camera)
{
	t_color	pixel_pos;
	t_vec3	ray_dir;
	t_ray	r;

	pixel_pos = vec3_add(vec3_add(camera->pixel00_loc,
				vec3_scalar_mul(camera->pixel_delta_u, x)),
			vec3_scalar_mul(camera->pixel_delta_v, y));
	ray_dir = vec3_unit(vec3_sub(pixel_pos, camera->center));
	r = ray(camera->center, ray_dir);
	return (r);
}

int	mouse_hook(int keycode, int x, int y, t_scene *scene)
{
	t_ray	ray;

	if (keycode == 1)
	{
		ray = create_ray_from_mouse(x, y, &scene->camera);
		select_object(scene, &ray);
		printf("%d\n", scene->type_selected_object);
	}
	return (0);
}
