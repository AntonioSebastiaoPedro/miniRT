/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:02:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:50:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	select_object(t_scene *scene, t_ray *ray)
{
	t_hit			hit_temp;
	t_ray_bounds	limits;

	limits = create_bounds(1e-64, __DBL_MAX__);
	if (is_hit(&scene->object_list, ray, &limits, &hit_temp))
	{
		if (hit_temp.type == SPHERE)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = SPHERE;
		}
		else if (hit_temp.type == PLANE)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = PLANE;
		}
		else if (hit_temp.type == CYLINDER)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = CYLINDER;
		}
	}
}

int	mouse_hook(int keycode, int x, int y, t_scene *scene)
{
	t_ray	ray;

	if (keycode == 1)
	{
		ray = create_ray_from_mouse(x, y, &scene->camera);
		select_object(scene, &ray);
	}
	return (0);
}

int	ft_hand_hook(int keycode, t_scene *scene)
{
	printf("Code %d\n", keycode);
	if (keycode == 65307)
		ft_close(scene);
	else if ((keycode >= 65361 && keycode <= 65364) || keycode == 65438
		|| keycode == 65436)
		translate_object(keycode, scene);
	else if (keycode == 97 || keycode == 100 || keycode == 119
		|| keycode == 115)
		resize(keycode, scene);
	else if (keycode == 114)
		reset_render(scene);
	else if (keycode == 99)
		scene->type_selected_object = CAMERA;
	else if (keycode == 108)
		scene->type_selected_object = LIGHT;
	else if ((keycode >= 105 && keycode <= 107) || (keycode >= 109
			&& keycode <= 111))
		rotate_object(keycode, scene);
	update_render(scene);
	return (0);
}
