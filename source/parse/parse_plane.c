/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:00 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_plane_vtn(t_scene *scene, char **tokens, t_token t)
{
	char	**vtn_tokens;
	double	length;

	vtn_tokens = ft_split(tokens[2], ',');
	scene->plane.normal.x = str_to_double(vtn_tokens[0], vtn_tokens, &t, scene);
	scene->plane.normal.y = str_to_double(vtn_tokens[1], vtn_tokens, &t, scene);
	scene->plane.normal.z = str_to_double(vtn_tokens[2], vtn_tokens, &t, scene);
	free_split(vtn_tokens);
	if (scene->plane.normal.x < -1.0 || scene->plane.normal.x > 1.0
		|| scene->plane.normal.y < -1.0 || scene->plane.normal.y > 1.0
		|| scene->plane.normal.z < -1.0 || scene->plane.normal.z > 1.0)
	{
		print_error_plane(tokens, t, 1, scene);
	}
	length = vec3_length(scene->plane.normal);
	if (length == 0)
		print_error_plane(tokens, t, 0, scene);
	scene->plane.normal = vec3_scalar_div(scene->plane.normal, length);
}

void	parse_plane_pos(t_scene *scene, char **tokens, t_token t)
{
	char	**pos_tks;
	char	*position_str;

	position_str = tokens[1];
	pos_tks = ft_split(position_str, ',');
	scene->plane.point.x = str_to_double(pos_tks[0], pos_tks, &t,
			scene);
	scene->plane.point.y = str_to_double(pos_tks[1], pos_tks, &t,
			scene);
	scene->plane.point.z = str_to_double(pos_tks[2], pos_tks, &t,
			scene);
	free_split(pos_tks);
}

void	parse_plane(t_token t, t_scene *scene)
{
	char	**tokens;

	tokens = ft_split(t.line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for plane: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(tokens, 4, t, scene);
	parse_plane_pos(scene, tokens, t);
	parse_plane_vtn(scene, tokens, t);
	scene->plane.color = parse_color(tokens, tokens[3], t, scene);
	free_split(tokens);
	scene->num_planes += 1;
	add_to_hittable_list(&scene->object_list, PLANE,
		create_plane(scene->plane));
}
