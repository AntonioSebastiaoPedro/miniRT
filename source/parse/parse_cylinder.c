/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:49:31 by ateca             #+#    #+#             */
/*   Updated: 2025/01/30 06:17:27 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	parse_height(char **tokens, char *token, char *line, int fd)
{
	char	*str_height;
	double	height;
	t_file	file;

	file.fd = fd;
	file.line = line;
	str_height = token;
	height = str_to_double(str_height, NULL, tokens, &file);
	return (height);
}

void	parse_cylinder_vtx(t_cylinder *cylinder, char **tokens, char *l, int fd)
{
	char	**vtx_tokens;
	double	length;
	t_file	file;

	file.fd = fd;
	file.line = l;
	vtx_tokens = ft_split(tokens[2], ',');
	cylinder->normal.x = str_to_double(vtx_tokens[0], vtx_tokens, tokens,
			&file);
	cylinder->normal.y = str_to_double(vtx_tokens[1], vtx_tokens, tokens,
			&file);
	cylinder->normal.z = str_to_double(vtx_tokens[2], vtx_tokens, tokens,
			&file);
	free_split(vtx_tokens);
	if (cylinder->normal.x < -1.0 || cylinder->normal.x > 1.0
		|| cylinder->normal.y < -1.0 || cylinder->normal.y > 1.0
		|| cylinder->normal.z < -1.0 || cylinder->normal.z > 1.0)
	{
		print_error_cylinder(tokens, file.line, fd, 1);
	}
	length = vec3_length(cylinder->normal);
	if (length == 0)
		print_error_cylinder(tokens, file.line, fd, 0);
	cylinder->normal = vec3_scalar_div(cylinder->normal, length);
}

void	parse_cylinder_center(t_cylinder *cyl, char **tokens, char *l, int fd)
{
	char	**cent_token;
	char	*cent_str;
	t_file	file;

	file.fd = fd;
	file.line = l;
	cent_str = tokens[1];
	cent_token = ft_split(cent_str, ',');
	cyl->center.x = str_to_double(cent_token[0], cent_token, tokens, &file);
	cyl->center.y = str_to_double(cent_token[1], cent_token, tokens, &file);
	cyl->center.z = str_to_double(cent_token[2], cent_token, tokens, &file);
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
		free_line_exit(line, fd);
	}
	validate_token_number(tokens, 6, line, fd);
	parse_cylinder_center(&scene->cylinder, tokens, line, fd);
	parse_cylinder_vtx(&scene->cylinder, tokens, line, fd);
	scene->cylinder.diameter = parse_diameter(tokens, tokens[3], line, fd);
	scene->cylinder.radius = scene->cylinder.diameter / 2.0;
	scene->cylinder.height = parse_height(tokens, tokens[4], line, fd);
	scene->cylinder.color = parse_color(tokens, tokens[5], line, fd);
	free_split(tokens);
	scene->num_cylinders += 1;
	add_to_hittable_list(&scene->object_list, CYLINDER, create_cylinder(scene->cylinder));
}
