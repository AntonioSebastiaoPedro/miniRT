/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:03:01 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 07:56:27 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIN_WIDTH, WIN_HEIGHT,
			"Akatsuki's \"mini Ray Tracer\"");
	scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	scene->object_list = NULL;
	scene->camera.aspect_ratio = 16.0 / 9.0;
	scene->camera.focal_length = 1.0;
	scene->camera.image_width = WIN_WIDTH;
	scene->selected_object = NULL;
	scene->type_selected_object = -1;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_close(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->mlx_win);
	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	free_scene(scene);
	exit(0);
	return (0);
}