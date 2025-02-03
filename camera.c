/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:51:04 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 16:41:59 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	viewport_init(t_viewport *viewport, t_camera *camera)
{
	double	fov_radians;
	t_vec3	right;
	t_vec3	up;

	right = vec3_unit(vec3_cross(vec3(0.0, 1.0, 0.0), camera->dvs));
	fov_radians = camera->fov * (PI / 180.0);
	viewport->height = 2.0 * tan(fov_radians / 2.0);
	viewport->width = viewport->height * camera->aspect_ratio;
	viewport->horizont = vec3_scalar_mul(right, viewport->width);
	up = vec3_unit(vec3_cross(camera->dvs, right));
	viewport->vertical = vec3_neg(vec3_scalar_mul(up, viewport->height));
}

void	camera_init(t_camera *camera, t_viewport *viewport)
{
	camera->image_height = (int)(camera->image_width / camera->aspect_ratio);
	if (camera->image_height < 1)
		camera->image_height = 1;
	viewport_init(viewport, camera);
	camera->pixel_delta_u = vec3_scalar_div(viewport->horizont,
			camera->image_width);
	camera->pixel_delta_v = vec3_scalar_div(viewport->vertical,
			camera->image_height);
	viewport->center = vec3_add(camera->center, vec3_scalar_mul(camera->dvs,
				camera->focal_length));
	viewport->upper_left = vec3_sub(vec3_sub(viewport->center,
				vec3_scalar_div(viewport->horizont, 2.0)),
			vec3_scalar_div(viewport->vertical, 2.0));
	camera->pixel00_loc = vec3_add(viewport->upper_left,
			vec3_scalar_mul(vec3_add(camera->pixel_delta_u,
					camera->pixel_delta_v), 0.5));
}

void	draw_background_bar(t_scene *scene, int start_y, int bg_color,
		t_img *img)
{
	int	i;
	int	j;

	j = 0;
	while (j < BAR_HEIGHT)
	{
		i = 0;
		while (i < scene->camera.image_width - 100)
		{
			my_mlx_pixel_put(img, BAR_START_X + i, start_y + j, bg_color);
			i++;
		}
		j++;
	}
}

void	draw_progress_segment(int bar_width, int start_y, t_img *img)
{
	int	i;
	int	j;

	j = 0;
	while (j < BAR_HEIGHT)
	{
		i = 0;
		while (i < bar_width)
		{
			my_mlx_pixel_put(img, BAR_START_X + i, start_y + j, PROGRESS_COLOR);
			i++;
		}
		j++;
	}
}

void	draw_progress_bar(t_scene *scene, int current_scanline,
		int total_scanlines, t_img *img)
{
	int	bar_width;
	int	start_y;

	start_y = scene->camera.image_height - BAR_HEIGHT - WIN_HEIGHT / 2;
	bar_width = (scene->camera.image_width - 100) * ((float)current_scanline
			/ total_scanlines);
	draw_background_bar(scene, start_y, BG_COLOR, img);
	draw_progress_segment(bar_width, start_y, img);
}
