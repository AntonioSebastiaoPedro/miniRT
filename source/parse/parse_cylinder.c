/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:49:31 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	parse_height(char *token, t_token t, t_scene *scene)
{
	char	*str_height;
	double	height;

	str_height = token;
	height = str_to_double(str_height, NULL, &t, scene);
	return (height);
}

void	parse_cylinder_vtx(t_scene *scene, char **tokens, t_token t)
{
	char	**vtx_tokens;
	double	length;

	vtx_tokens = ft_split(tokens[2], ',');
	scene->cylinder.normal.x = str_to_double(vtx_tokens[0], vtx_tokens, &t,
			scene);
	scene->cylinder.normal.y = str_to_double(vtx_tokens[1], vtx_tokens, &t,
			scene);
	scene->cylinder.normal.z = str_to_double(vtx_tokens[2], vtx_tokens, &t,
			scene);
	free_split(vtx_tokens);
	if (scene->cylinder.normal.x < -1.0 || scene->cylinder.normal.x > 1.0
		|| scene->cylinder.normal.y < -1.0 || scene->cylinder.normal.y > 1.0
		|| scene->cylinder.normal.z < -1.0 || scene->cylinder.normal.z > 1.0)
	{
		print_error_cylinder(tokens, t, 1, scene);
	}
	length = vec3_length(scene->cylinder.normal);
	if (length == 0)
		print_error_cylinder(tokens, t, 0, scene);
	scene->cylinder.normal = vec3_scalar_div(scene->cylinder.normal, length);
}

void	parse_cylinder_center(t_scene *scene, char **tokens, t_token t)
{
	char	**cent_token;
	char	*cent_str;

	cent_str = tokens[1];
	cent_token = ft_split(cent_str, ',');
	scene->cylinder.center.x = str_to_double(cent_token[0], cent_token, &t,
			scene);
	scene->cylinder.center.y = str_to_double(cent_token[1], cent_token, &t,
			scene);
	scene->cylinder.center.z = str_to_double(cent_token[2], cent_token, &t,
			scene);
	free_split(cent_token);
}

void	parse_cylinder(t_token t, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(t.line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		free_split(tokens);
		print_error("Invalid format for cylinder: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(tokens, 6, t, scene);
	parse_cylinder_center(scene, tokens, t);
	parse_cylinder_vtx(scene, tokens, t);
	scene->cylinder.diameter = parse_diameter(tokens[3], t, scene);
	scene->cylinder.radius = scene->cylinder.diameter / 2.0;
	scene->cylinder.height = parse_height(tokens[4], t, scene);
	scene->cylinder.color = parse_color(tokens, tokens[5], t, scene);
	free_split(tokens);
	scene->num_cylinders += 1;
	add_to_hittable_list(&scene->object_list, CYLINDER,
		create_cylinder(scene->cylinder));
}
