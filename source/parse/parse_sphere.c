/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:56:50 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_sphere_center(t_scene *scene, char **tokens, t_token t)
{
	char	**cent_token;
	char	*cent_str;

	cent_str = tokens[1];
	cent_token = ft_split(cent_str, ',');
	scene->sphere.center.x = str_to_double(cent_token[0], cent_token, &t,
			scene);
	scene->sphere.center.y = str_to_double(cent_token[1], cent_token, &t,
			scene);
	scene->sphere.center.z = str_to_double(cent_token[2], cent_token, &t,
			scene);
	free_split(cent_token);
}

void	parse_sphere(t_token t, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(t.line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for sphere: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(tokens, 4, t, scene);
	parse_sphere_center(scene, tokens, t);
	scene->sphere.diameter = parse_diameter(tokens[2], t, scene);
	scene->sphere.radius = fmax(0.0, scene->sphere.diameter / 2.0);
	scene->sphere.color = parse_color(tokens, tokens[3], t, scene);
	free_split(tokens);
	scene->num_spheres += 1;
	add_to_hittable_list(&scene->object_list, SPHERE,
		create_sphere(scene->sphere));
}
