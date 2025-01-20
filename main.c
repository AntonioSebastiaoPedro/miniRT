/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/17 18:02:31 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_camara		camara;
	t_viewport		viewport;
	t_hittable_list	list;

	camara.center = vec3_zero();
	camara.aspect_ratio = 16.0 / 9.0;
	camara.image_width = WIN_WIDTH;
	camara.max_depth = 10;
	camara_init(&camara, &viewport);
	list = create_hittable_list(3);
	add_hittable(&list, create_sphere(vec3(0.0, 0.0, -1.0), 0.5));
	add_hittable(&list, create_sphere(vec3(0.0, -100.5, -1.0), 100.0));
	render_image(&camara, &list);
	return (0);
}
