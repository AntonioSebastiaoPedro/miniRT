/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:00 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:51:00 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_plane_vtn(t_plane *plane, char **tokens, char *line, int fd)
{
	char	**vtn_tokens;
	double	length;
	t_file	file;

	file.fd = fd;
	file.line = line;
	vtn_tokens = ft_split(tokens[2], ',');
	plane->normal.x = str_to_double(vtn_tokens[0], vtn_tokens, tokens, &file);
	plane->normal.y = str_to_double(vtn_tokens[1], vtn_tokens, tokens, &file);
	plane->normal.z = str_to_double(vtn_tokens[2], vtn_tokens, tokens, &file);
	free_split(vtn_tokens);
	if (plane->normal.x < -1.0 || plane->normal.x > 1.0
		|| plane->normal.y < -1.0 || plane->normal.y > 1.0
		|| plane->normal.z < -1.0 || plane->normal.z > 1.0)
	{
		print_error_plane(tokens, line, fd, 1);
	}
	length = sqrt(plane->normal.x * plane->normal.x
			+ plane->normal.y * plane->normal.y
			+ plane->normal.z * plane->normal.z);
	if (length == 0)
		print_error_plane(tokens, line, fd, 0);
	plane->normal.x /= length;
	plane->normal.y /= length;
	plane->normal.z /= length;
}

void	parse_plane_pos(t_plane *plane, char **tokens, char *line, int fd)
{
	char	**pos_tks;
	char	*position_str;
	t_file	file;

	file.fd = fd;
	file.line = line;
	position_str = tokens[1];
	pos_tks = ft_split(position_str, ',');
	plane->point.x = str_to_double(pos_tks[0], pos_tks, tokens, &file);
	plane->point.y = str_to_double(pos_tks[1], pos_tks, tokens, &file);
	plane->point.z = str_to_double(pos_tks[2], pos_tks, tokens, &file);
	free_split(pos_tks);
}

void	parse_plane(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for plane: ", line);
		free_line_exit(line, fd);
	}
	validate_token_number(tokens, 4, line, fd);
	parse_plane_pos(&scene->plane, tokens, line, fd);
	parse_plane_vtn(&scene->plane, tokens, line, fd);
	scene->plane.color = parse_color(tokens, tokens[3], line, fd);
	// printf("Plano:\n");
	// printf("  Posição: (%.2f, %.2f, %.2f)\n", scene->plane.point.x,
	// 	scene->plane.point.y, scene->plane.point.z);
	// printf("  Vector normal: (%.2f, %.2f, %.2f)\n", scene->plane.normal.x,
	// 	scene->plane.normal.y, scene->plane.normal.z);
	// printf("  Cor:   (%d, %d, %d)\n", scene->plane.color.x,
	// 	scene->plane.color.y, scene->plane.color.z);
	free_split(tokens);
	scene->num_planes += 1;
	printf("Plano: %d\n", scene->num_planes);
}
