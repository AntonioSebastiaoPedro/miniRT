/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/08 19:58:18 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
	{
		print_error("Use : ./miniRT <file.rt>", NULL);
		exit(2);
	}
	init_scene(&scene);
	parse_file(av[1], &scene);
	scene.map = av[1];
	scene.mlx = mlx_init();
	scene.mlx_win = mlx_new_window(scene.mlx, WIN_WIDTH, WIN_HEIGHT,
			"Akatsuki's \"mini Ray Tracer\"");
	scene.img.img = mlx_new_image(scene.mlx, WIN_WIDTH, WIN_HEIGHT);
	scene.img.addr = mlx_get_data_addr(scene.img.img, &scene.img.bits_per_pixel,
			&scene.img.line_length, &scene.img.endian);
	camera_init(&scene.camera, &scene.viewport);
	render_image(&scene, true);
	mlx_put_image_to_window(scene.mlx, scene.mlx_win, scene.img.img, 0, 0);
	mlx_hook(scene.mlx_win, 17, 1L << 0, ft_close, &scene);
	mlx_hook(scene.mlx_win, 2, 1L << 0, ft_hand_hook, &scene);
	mlx_mouse_hook(scene.mlx_win, mouse_hook, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
