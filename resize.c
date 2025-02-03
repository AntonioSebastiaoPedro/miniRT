/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:04:16 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 15:28:47 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resize_width(t_scene *scene, double value)
{
	t_sphere	*sp;
	t_cylinder	*cy;

	if (scene->type_selected_object == SPHERE)
	{
		sp = (t_sphere *)scene->selected_object;
		sp->diameter = fmax(1, sp->diameter + value);
		sp->radius = sp->diameter / 2;
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->diameter = fmax(1, cy->diameter + value);
		cy->radius = cy->diameter / 2;
	}
}

void	resize_height(t_scene *scene, double value)
{
	t_cylinder	*cy;

	if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->height = fmax(1, cy->height + value);
	}
}

void	resize(int keycode, t_scene *scene)
{
	if (keycode == 97)
		resize_width(scene, 1);
	else if (keycode == 100)
		resize_width(scene, -1);
	else if (keycode == 119)
		resize_height(scene, 1);
	else if (keycode == 115)
		resize_height(scene, -1);
}
