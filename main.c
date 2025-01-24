/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/24 16:07:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_camara	camara;
	t_viewport	viewport;
	t_hittable	*list;

	list = NULL;
	camara.center = vec3(0.0, 0.0, 0.0);
	camara.orientation = vec3(0.0, 0.0, 1.0);
	camara.aspect_ratio = 16.0 / 9.0;
	camara.focal_length = 1.0;
	camara.fov = 70.0;
	camara.image_width = WIN_WIDTH;
	camara_init(&camara, &viewport);
	add_to_hittable_list(&list, 0, create_sphere(vec3(0.0, 0.0, 10.0), color(1.0, 0.0, 0.0),
			1.6));
	render_image(&camara, &list);
	return (0);
}
