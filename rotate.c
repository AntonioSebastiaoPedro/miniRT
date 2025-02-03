/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:02:27 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 15:25:10 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_x(t_scene *scene, double angle)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (scene->type_selected_object == PLANE)
	{
		pl = (t_plane *)scene->selected_object;
		pl->normal = vec3_unit(vec3_rotate_x(pl->normal, angle));
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->normal = vec3_unit(vec3_rotate_x(cy->normal, angle));
	}
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.dvs = vec3_unit(vec3_rotate_x(scene->camera.dvs, angle));
		camera_init(&scene->camera, &scene->viewport);
	}
}

void	rotate_y(t_scene *scene, double angle)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (scene->type_selected_object == PLANE)
	{
		pl = (t_plane *)scene->selected_object;
		pl->normal = vec3_unit(vec3_rotate_y(pl->normal, angle));
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->normal = vec3_unit(vec3_rotate_y(cy->normal, angle));
	}
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.dvs = vec3_unit(vec3_rotate_y(scene->camera.dvs, angle));
		camera_init(&scene->camera, &scene->viewport);
	}
}

void	rotate_z(t_scene *scene, double angle)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (scene->type_selected_object == PLANE)
	{
		pl = (t_plane *)scene->selected_object;
		pl->normal = vec3_unit(vec3_rotate_z(pl->normal, angle));
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->normal = vec3_unit(vec3_rotate_z(cy->normal, angle));
	}
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.dvs = vec3_unit(vec3_rotate_z(scene->camera.dvs, angle));
		camera_init(&scene->camera, &scene->viewport);
	}
}

void	rotate_object(int keycode, t_scene *scene)
{
	if (keycode == 105)
		rotate_x(scene, -PI / 20);
	else if (keycode == 111)
		rotate_x(scene, PI / 20);
	else if (keycode == 106)
		rotate_y(scene, -PI / 20);
	else if (keycode == 107)
		rotate_y(scene, PI / 20);
	else if (keycode == 110)
		rotate_z(scene, -PI / 20);
	else if (keycode == 109)
		rotate_z(scene, PI / 20);
}
