/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:33:55 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:49:07 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	translate(t_scene *scene, t_vec3 translation)
{
	if (scene->type_selected_object == SPHERE)
		((t_sphere *)scene->selected_object)->center = \
			vec3_add(((t_sphere *)scene->selected_object)->center, translation);
	else if (scene->type_selected_object == PLANE)
		((t_plane *)scene->selected_object)->point = \
			vec3_add(((t_plane *)scene->selected_object)->point, translation);
	else if (scene->type_selected_object == CYLINDER)
		((t_cylinder *)scene->selected_object)->center = \
			vec3_add(((t_cylinder *)scene->selected_object)->center,
				translation);
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.center = vec3_add(scene->camera.center,
				vec3_scalar_div(translation, 3));
		camera_init(&scene->camera, &scene->viewport);
	}
	else if (scene->type_selected_object == LIGHT)
	{
		scene->light.position = vec3_add(scene->light.position,
				vec3_scalar_div(translation, 2));
	}
}

void	translate_object(int keycode, t_scene *scene)
{
	if (keycode == 65361)
		translate(scene, vec3(-1, 0, 0));
	else if (keycode == 65363)
		translate(scene, vec3(1, 0, 0));
	else if (keycode == 65362)
		translate(scene, vec3(0, 1, 0));
	else if (keycode == 65364)
		translate(scene, vec3(0, -1, 0));
	else if (keycode == 65438)
		translate(scene, vec3(0, 0, -1));
	else if (keycode == 65436)
		translate(scene, vec3(0, 0, 1));
}
