/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:49:31 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:53:23 by ansebast         ###   ########.fr       */
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
	cylinder->normal.x = str_to_double(vtx_tokens[0], vtx_tokens, tokens, &file);
	cylinder->normal.y = str_to_double(vtx_tokens[1], vtx_tokens, tokens, &file);
	cylinder->normal.z = str_to_double(vtx_tokens[2], vtx_tokens, tokens, &file);
	free_split(vtx_tokens);
	if (cylinder->normal.x < -1.0 || cylinder->normal.x > 1.0
		|| cylinder->normal.y < -1.0 || cylinder->normal.y > 1.0
		|| cylinder->normal.z < -1.0 || cylinder->normal.z > 1.0)
	{
		print_error_cylinder(tokens, file.line, fd, 1);
	}
	length = sqrt(cylinder->normal.x * cylinder->normal.x
			+ cylinder->normal.y * cylinder->normal.y
			+ cylinder->normal.z * cylinder->normal.z);
	if (length == 0)
		print_error_cylinder(tokens, file.line, fd, 0);
	cylinder->normal.x /= length;
	cylinder->normal.y /= length;
	cylinder->normal.z /= length;
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
	scene->cylinder.height = parse_height(tokens, tokens[4], line, fd);
	scene->cylinder.color = parse_color(tokens, tokens[5], line, fd);
	// printf("Cilíndro:\n");
	// printf("  Centro: (%.2f, %.2f, %.2f)\n", scene->cylinder.center.x,
	// 	scene->cylinder.center.y, scene->cylinder.center.z);
	// printf("  Vector eixo: (%.2f, %.2f, %.2f)\n", scene->cylinder.normal.x,
	// 	scene->cylinder.normal.y, scene->cylinder.normal.z);
	// printf("  Diametro: %.2f\n", scene->cylinder.diameter);
	// printf("  Altura: %.2f\n", scene->cylinder.height);
	// printf("  Cor:   (%d, %d, %d)\n", scene->cylinder.color.x,
	// 	scene->cylinder.color.y, scene->cylinder.color.z);
	free_split(tokens);
	scene->num_cylinders += 1;
	printf("Cilíndro: %d\n", scene->num_cylinders);
}
