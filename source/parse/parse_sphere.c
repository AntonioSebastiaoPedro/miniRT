/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:56:50 by ateca             #+#    #+#             */
/*   Updated: 2025/02/02 19:36:09 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_sphere_center(t_scene *scene, char **tokens, char *line, int fd)
{
	char	**cent_token;
	char	*cent_str;
	t_file	file;

	file.fd = fd;
	file.line = line;
	cent_str = tokens[1];
	cent_token = ft_split(cent_str, ',');
	scene->sphere.center.x = str_to_double(cent_token[0], cent_token, tokens, &file, scene);
	scene->sphere.center.y = str_to_double(cent_token[1], cent_token, tokens, &file, scene);
	scene->sphere.center.z = str_to_double(cent_token[2], cent_token, tokens, &file, scene);
	free_split(cent_token);
}

void	parse_sphere(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for sphere: ", line);
		free_line_exit(line, fd, scene);
	}
	validate_token_number(tokens, 4, line, fd, scene);
	parse_sphere_center(scene, tokens, line, fd);
	scene->sphere.diameter = parse_diameter(tokens, tokens[2], line, fd, scene);
	scene->sphere.radius = fmax(0.0, scene->sphere.diameter / 2.0);
	scene->sphere.color = parse_color(tokens, tokens[3], line, fd, scene);
	free_split(tokens);
	scene->num_spheres += 1;
	add_to_hittable_list(&scene->object_list, SPHERE, create_sphere(scene->sphere));
}
