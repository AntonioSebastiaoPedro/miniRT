/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camara.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:51:04 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/24 17:09:23 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	viewport_init(t_viewport *viewport, t_camara *camara)
{
	double	fov_radians;
	t_vec3	right;
	t_vec3	up;

	right = vec3_unit(vec3_cross(vec3(0.0, 1.0, 0.0), camara->orientation));
	fov_radians = camara->fov * (PI / 180.0);
	viewport->height = 2.0 * tan(fov_radians / 2.0);
	viewport->width = viewport->height * camara->aspect_ratio;
	viewport->horizont = vec3_scalar_mul(right, viewport->width);
	up = vec3_unit(vec3_cross(camara->orientation, right));
	viewport->vertical = vec3_neg(vec3_scalar_mul(up, viewport->height));
}

void	camara_init(t_camara *camara, t_viewport *viewport)
{
	camara->image_height = (int)(camara->image_width / camara->aspect_ratio);
	if (camara->image_height < 1)
		camara->image_height = 1;
	viewport_init(viewport, camara);
	camara->pixel_delta_u = vec3_scalar_div(viewport->horizont,
			camara->image_width);
	camara->pixel_delta_v = vec3_scalar_div(viewport->vertical,
			camara->image_height);
	viewport->center = vec3_add(camara->center,
			vec3_scalar_mul(camara->orientation, camara->focal_length));
	viewport->upper_left = vec3_sub(vec3_sub(viewport->center,
				vec3_scalar_div(viewport->horizont, 2.0)),
			vec3_scalar_div(viewport->vertical, 2.0));
	camara->pixel00_loc = vec3_add(viewport->upper_left,
			vec3_scalar_mul(vec3_add(camara->pixel_delta_u,
					camara->pixel_delta_v), 0.5));
}

void	render_image(t_camara *camara, t_hittable **list, t_scene *scene)
{
	int		fd;
	int		i;
	int		j;
	t_color	pixel_color;
	t_vec3	pixel_pos;
	t_vec3	ray_direction;
	t_ray	r;

	fd = open("image.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(fd, "P3\n%d %d\n255\n", camara->image_width, camara->image_height);
	j = 0;
	while (j < camara->image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d", camara->image_height - j);
		fflush(stderr);
		i = 0;
		while (i < camara->image_width)
		{
			pixel_pos = vec3_add(vec3_add(camara->pixel00_loc,
						vec3_scalar_mul(camara->pixel_delta_u, i)),
					vec3_scalar_mul(camara->pixel_delta_v, j));
			ray_direction = vec3_sub(pixel_pos, camara->center);
			r = ray(camara->center, ray_direction);
			pixel_color = ray_color(&r, list, scene);
			write_color(fd, pixel_color);
			i++;
		}
		j++;
	}
	close(fd);
	fprintf(stderr, "\nDone.\n");
}
