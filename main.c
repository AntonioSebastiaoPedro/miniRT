/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/30 06:36:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_viewport	viewport;
	t_scene		scene;

	if (ac != 2)
	{
		print_error("Use : ./miniRT <file.rt>", NULL);
		exit(2);
	}
	init_scene(&scene);
	parse_file(av[1], &scene);
	camera_init(&scene.camera, &viewport);
	render_image(&scene.camera, &scene.object_list, &scene);
	mlx_put_image_to_window(scene.mlx, scene.mlx_win, scene.img.img, 0, 0);
	mlx_hook(scene.mlx_win, 17, 1L << 0, ft_close, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
