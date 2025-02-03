/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:40 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:17 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_render(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	render_image(&scene->camera, &scene->object_list, scene, false);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
}

void	reset_render(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	free_scene(scene);
	scene->selected_object = NULL;
	scene->type_selected_object = -1;
	parse_file(scene->map, scene);
	camera_init(&scene->camera, &scene->viewport);
	render_image(&scene->camera, &scene->object_list, scene, true);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
}
