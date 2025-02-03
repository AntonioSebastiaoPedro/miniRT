/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:49:31 by ateca             #+#    #+#             */
/*   Updated: 2025/02/02 19:41:06 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	parse_height(char **tokens, char *token, char *line, int fd, t_scene *scene)
{
	char	*str_height;
	double	height;
	t_file	file;

	file.fd = fd;
	file.line = line;
	str_height = token;
	height = str_to_double(str_height, NULL, tokens, &file, scene);
	return (height);
}

void	parse_cylinder_vtx(t_scene *scene, char **tokens, char *l, int fd)
{
	char	**vtx_tokens;
	double	length;
	t_file	file;

	file.fd = fd;
	file.line = l;
	vtx_tokens = ft_split(tokens[2], ',');
	scene->cylinder.normal.x = str_to_double(vtx_tokens[0], vtx_tokens, tokens,
			&file, scene);
	scene->cylinder.normal.y = str_to_double(vtx_tokens[1], vtx_tokens, tokens,
			&file, scene);
	scene->cylinder.normal.z = str_to_double(vtx_tokens[2], vtx_tokens, tokens,
			&file, scene);
	free_split(vtx_tokens);
	if (scene->cylinder.normal.x < -1.0 || scene->cylinder.normal.x > 1.0
		|| scene->cylinder.normal.y < -1.0 || scene->cylinder.normal.y > 1.0
		|| scene->cylinder.normal.z < -1.0 || scene->cylinder.normal.z > 1.0)
	{
		print_error_cylinder(tokens, file.line, fd, 1, scene);
	}
	length = vec3_length(scene->cylinder.normal);
	if (length == 0)
		print_error_cylinder(tokens, file.line, fd, 0, scene);
	scene->cylinder.normal = vec3_scalar_div(scene->cylinder.normal, length);
}

void	parse_cylinder_center(t_scene *scene, char **tokens, char *l, int fd)
{
	char	**cent_token;
	char	*cent_str;
	t_file	file;

	file.fd = fd;
	file.line = l;
	cent_str = tokens[1];
	cent_token = ft_split(cent_str, ',');
	scene->cylinder.center.x = str_to_double(cent_token[0], cent_token, tokens, &file, scene);
	scene->cylinder.center.y = str_to_double(cent_token[1], cent_token, tokens, &file, scene);
	scene->cylinder.center.z = str_to_double(cent_token[2], cent_token, tokens, &file, scene);
	free_split(cent_token);
}

void	parse_cylinder(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		free_split(tokens);
		print_error("Invalid format for cylinder: ", line);
		free_line_exit(line, fd, scene);
	}
	validate_token_number(tokens, 6, line, fd, scene);
	parse_cylinder_center(scene, tokens, line, fd);
	parse_cylinder_vtx(scene, tokens, line, fd);
	scene->cylinder.diameter = parse_diameter(tokens, tokens[3], line, fd, scene);
	scene->cylinder.radius = scene->cylinder.diameter / 2.0;
	scene->cylinder.height = parse_height(tokens, tokens[4], line, fd, scene);
	scene->cylinder.color = parse_color(tokens, tokens[5], line, fd, scene);
	free_split(tokens);
	scene->num_cylinders += 1;
	add_to_hittable_list(&scene->object_list, CYLINDER, create_cylinder(scene->cylinder));
}
