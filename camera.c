/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:51:04 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/29 21:04:44 by ansebast         ###   ########.fr       */
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
	viewport->center = vec3_add(camera->center,
			vec3_scalar_mul(camera->dvs, camera->focal_length));
	viewport->upper_left = vec3_sub(vec3_sub(viewport->center,
				vec3_scalar_div(viewport->horizont, 2.0)),
			vec3_scalar_div(viewport->vertical, 2.0));
	camera->pixel00_loc = vec3_add(viewport->upper_left,
			vec3_scalar_mul(vec3_add(camera->pixel_delta_u,
					camera->pixel_delta_v), 0.5));
}

void	render_image(t_camera *camera, t_hittable **list, t_scene *scene)
{
	int		i;
	int		j;
	t_color	pixel_color;
	t_vec3	pixel_pos;
	t_vec3	ray_direction;
	t_ray	r;

	j = 0;
	while (j < camera->image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d", camera->image_height - j);
		fflush(stderr);
		i = 0;
		while (i < camera->image_width)
		{
			pixel_pos = vec3_add(vec3_add(camera->pixel00_loc,
						vec3_scalar_mul(camera->pixel_delta_u, i)),
					vec3_scalar_mul(camera->pixel_delta_v, j));
			ray_direction = vec3_sub(pixel_pos, camera->center);
			r = ray(camera->center, ray_direction);
			pixel_color = ray_color(&r, list, scene);
			my_mlx_pixel_put(&scene->img, i, j, color_to_int(pixel_color));
			i++;
		}
		j++;
	}
	fprintf(stderr, "\nDone.\n");
}
