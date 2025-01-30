/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/29 21:44:01 by ansebast         ###   ########.fr       */
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
	
	// scene.ambient_light.intensity = 0.2;
	// scene.ambient_light.color = color(255, 255, 255);

	// scene.light.brightness = 0.7;
	// scene.light.position = vec3(0.0, 0.5, -4.5);
	// scene.light.color = color(255, 255, 255);

	// camera.center = vec3(0.0, 1.0, -10.0);
	// camera.dvs = vec3_unit(vec3(0.0, 0.0, 1.0));


	camera_init(&scene.camera, &viewport);

	// add_to_hittable_list(&scene.object_list, 1, create_plane(
	// 	vec3(-5.0, 0.0, 0.0),
	// 	vec3(1.0, 0.0, 0.0), 
	// 	color(25, 179, 153) 
	// ));
	// add_to_hittable_list(&scene.object_list, 1, create_plane(
	// 	vec3(5.0, 0.0, 0.0),
	// 	vec3(-1.0, 0.0, 0.0), 
	// 	color(255, 179, 26)
	// ));

	// add_to_hittable_list(&scene.object_list, 1, create_plane(
	// 	vec3(0.0, -1.0, 0.0),
	// 	vec3(0.0, 1.0, 0.0), 
	// 	color(255, 255, 255) 
	// ));
	// add_to_hittable_list(&scene.object_list, 1, create_plane(
	// 	vec3(0.0, 3.0, 0.0),
	// 	vec3(0.0, -1.0, 0.0), 
	// 	color(255, 255, 255) 
	// ));
	// add_to_hittable_list(&scene.object_list, 1, create_plane(
	// 	vec3(0.0, 0.0, 5.0),
	// 	vec3(0.0, 0.0, -1.0), 
	// 	color(230, 128, 26) 
	// ));



	// add_to_hittable_list(&scene.object_list, 0, create_sphere(
	// 	vec3(2.0, 0.0, -2.0),
	// 	color(0, 255, 0),
	// 	1.0                  
	// ));
	// add_to_hittable_list(&scene.object_list, 0, create_sphere(
	// 	vec3(0.0, 0, 3.0),
	// 	color(255, 0, 0),
	// 	1                  
	// ));

	// add_to_hittable_list(&scene.object_list, 2, create_cylinder(
	// 	vec3(-1.5, -1, -0.5),
	// 	vec3(0.0, 1.0, 0.0),
	// 	color(0, 0, 255),
	// 	1.5,
	// 	2.5
	// ));
	render_image(&scene.camera, &scene.object_list, &scene);
	mlx_put_image_to_window(scene.mlx, scene.mlx_win, scene.img.img, 0, 0);
	mlx_hook(scene.mlx_win, 17, 1L << 0, ft_close, &scene);
	mlx_loop(scene.mlx);
	return (0);
}