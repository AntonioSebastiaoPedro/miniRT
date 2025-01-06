/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 10:49:24 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	int		image_width;
	int		image_height;
	int		j;
	int		i;

	image_width = WIN_WIDTH;
	image_height = WIN_HEIGHT;
	int fd = open("image.ppm", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(fd, "P3\n%d %d\n255\n", image_width, image_height);
	j = 0;
	while (j < image_height)
	{
		fprintf(stderr, "\rScanlines remaining: %d", image_height - j);
		fflush(stderr);
		i = 0;
		while (i < image_width)
		{
			t_color pixel_color = vec3((double)i / (image_width - 1), (double)j / (image_height - 1), 0.0);
			write_color(fd, pixel_color);
			i++;
		}
		j++;
	}
	close(fd);
	fprintf(stderr, "\nDone.\n");
	return (0);
}
