/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/08 18:11:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	int		image_width;
	int		image_height;
	int		j;
	int		i;
	double	aspect_ratio;
	int		fd;
	t_vec3	pixel_color;

 	// Configuração da imagem
	image_width = WIN_WIDTH;
	image_height = WIN_HEIGHT;
	aspect_ratio = 16.0 / 9.0;

	// Configuração da câmera
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)image_width / image_height);
	t_vec3 camera_center = vec3_zero();

	// Vetores do viewport
	t_vec3 viewport_u = vec3(viewport_width, 0, 0);
	t_vec3 viewport_v = vec3(0, -viewport_height, 0);

	// Delta entre os pixels
	t_vec3 pixel_delta_u = vec3_scalar_div(viewport_u, image_width);
	t_vec3 pixel_delta_v = vec3_scalar_div(viewport_v, image_height);

	// Posição inicial do pixel no canto superior esquerdo
	t_vec3 viewport_upper_left = vec3_sub(
		vec3_sub(vec3_sub(camera_center, vec3(0, 0, focal_length)),
			vec3_scalar_div(viewport_u, 2)),
		vec3_scalar_div(viewport_v, 2)
	);
	t_vec3 pixel00_loc = vec3_add(viewport_upper_left,
					vec3_scalar_mul(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));
	
	// Calcular a altura da imagem, garantindo que seja pelo menos 1
	image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;
	fd = open("image.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(fd, "P3\n%d %d\n255\n", image_width, image_height);
	j = 0;
	while (j < image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d", image_height - j);
		fflush(stderr);
		i = 0;
		while (i < image_width)
		{
			t_vec3 pixel_center = vec3_add(
				vec3_add(pixel00_loc, vec3_scalar_mul(pixel_delta_u, i)),
				vec3_scalar_mul(pixel_delta_v, j)
            		);
			t_vec3 ray_direction = vec3_sub(pixel_center, camera_center);
			t_ray r = ray(camera_center, ray_direction);

			pixel_color = ray_color(&r);
			write_color(fd, pixel_color);
			i++;
		}
		j++;
	}
	close(fd);
	fprintf(stderr, "\nDone.\n");
	return (0);
}
