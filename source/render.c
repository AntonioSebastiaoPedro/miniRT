/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:30:40 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:51:16 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	update_render(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	render_image(scene, false);
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
	render_image(scene, true);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
}

void	render_pixel(t_scene *scene, int i, int j)
{
	t_color	pixel_color;
	t_vec3	pixel_pos;
	t_vec3	ray_direction;
	t_ray	r;

	pixel_pos = vec3_add(vec3_add(scene->camera.pixel00_loc,
				vec3_scalar_mul(scene->camera.pixel_delta_u, i)),
			vec3_scalar_mul(scene->camera.pixel_delta_v, j));
	ray_direction = vec3_sub(pixel_pos, scene->camera.center);
	r = ray(scene->camera.center, ray_direction);
	pixel_color = ray_color(&r, &scene->object_list, scene);
	my_mlx_pixel_put(&scene->img, i, j, color_to_int(pixel_color));
}

void	render_scanline(t_scene *scene, int j, t_img *prog_bar,
		bool progress_bar)
{
	int	i;

	i = 0;
	while (i < scene->camera.image_width)
	{
		render_pixel(scene, i, j);
		i++;
	}
	if (progress_bar)
	{
		draw_progress_bar(scene, j, scene->camera.image_height, prog_bar);
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, prog_bar->img, 0,
			0);
	}
}

void	render_image(t_scene *scene, bool progress_bar)
{
	int		j;
	t_img	prog_bar;

	prog_bar.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	prog_bar.addr = mlx_get_data_addr(prog_bar.img, &prog_bar.bits_per_pixel,
			&prog_bar.line_length, &prog_bar.endian);
	j = 0;
	while (j < scene->camera.image_height)
	{
		render_scanline(scene, j, &prog_bar, progress_bar);
		j++;
	}
	mlx_destroy_image(scene->mlx, prog_bar.img);
}
