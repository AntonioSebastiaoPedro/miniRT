/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/29 12:21:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_camara	camara;
	t_viewport	viewport;
	t_hittable	*list;
	t_scene		scene;

	list = NULL;

	scene.ambient_light.intensity = 0.2;
	scene.ambient_light.color = color(1.0, 1.0, 1.0);


	scene.light.brightness = 1.0;
	scene.light.position = vec3(0.0, 1.5, -4.5);
	scene.light.color = color(1.0, 1.0, 1.0);


	camara.center = vec3(0.0, 1.0, -10.0);
	camara.orientation = vec3_unit(vec3(0.0, 0.0, 1.0));
	camara.aspect_ratio = 16.0 / 9.0;
	camara.focal_length = 1.0;
	camara.fov = 60.0;
	camara.image_width = WIN_WIDTH;


	camara_init(&camara, &viewport);

	add_to_hittable_list(&list, 1, create_plane(
		vec3(-5.0, 0.0, 0.0),
		vec3(1.0, 0.0, 0.0), 
		color(0.1, 0.7, 0.6) 
	));
	add_to_hittable_list(&list, 1, create_plane(
		vec3(5.0, 0.0, 0.0),
		vec3(-1.0, 0.0, 0.0), 
		color(1.0, 0.7, 0.1)
	));

	add_to_hittable_list(&list, 1, create_plane(
		vec3(0.0, -1.0, 0.0),
		vec3(0.0, 1.0, 0.0), 
		color(1.0, 1.0, 1.0) 
	));
	add_to_hittable_list(&list, 1, create_plane(
		vec3(0.0, 3.0, 0.0),
		vec3(0.0, -1.0, 0.0), 
		color(1.0, 1.0, 1.0) 
	));
	add_to_hittable_list(&list, 1, create_plane(
		vec3(0.0, 0.0, 5.0),
		vec3(0.0, 0.0, -1.0), 
		color(0.9, 0.5, 1.0) 
	));



	add_to_hittable_list(&list, 0, create_sphere(
		vec3(2.0, 0.0, -2.0),
		color(0.0, 1.0, 0.0),
		1.0                  
	));
	add_to_hittable_list(&list, 0, create_sphere(
		vec3(0.0, 0, 3.0),
		color(1.0, 0.0, 0.0),
		1                  
	));

	add_to_hittable_list(&list, 2, create_cylinder(
		vec3(-1.5, -1, -0.5),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0),
		1.5,
		2.5
	));
	render_image(&camara, &list, &scene);
	return (0);
}