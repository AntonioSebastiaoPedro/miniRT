/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:15:05 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:14:34 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_camera_fov(t_scene *scene, char **tokens, t_token t)
{
	char	*fov_str;

	fov_str = tokens[3];
	scene->camera.fov = str_to_double(fov_str, NULL, &t, scene);
	if (scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
	{
		print_error("Invalid FOV for camera (must be in the range [0,180]): ",
			t.line);
		free_split(tokens);
		free_line_exit(t.line, t.fd, scene);
	}
}

void	parse_camera_dvs(t_scene *scene, char **tokens, t_token t)
{
	char	**dvs_tokens;
	double	length;

	dvs_tokens = ft_split(tokens[2], ',');
	scene->camera.dvs.x = str_to_double(dvs_tokens[0], dvs_tokens, &t, scene);
	scene->camera.dvs.y = str_to_double(dvs_tokens[1], dvs_tokens, &t, scene);
	scene->camera.dvs.z = str_to_double(dvs_tokens[2], dvs_tokens, &t, scene);
	free_split(dvs_tokens);
	if (scene->camera.dvs.x < -1.0 || scene->camera.dvs.x > 1.0
		|| scene->camera.dvs.y < -1.0 || scene->camera.dvs.y > 1.0
		|| scene->camera.dvs.z < -1.0 || scene->camera.dvs.z > 1.0)
	{
		print_error_camera(tokens, t, 1, scene);
	}
	length = vec3_length(scene->camera.dvs);
	if (length == 0)
		print_error_camera(tokens, t, 0, scene);
	scene->camera.dvs = vec3_scalar_div(scene->camera.dvs, length);
}

void	parse_camera_pos(t_scene *scene, char **tokens, t_token t)
{
	char	**pos_tks;
	char	*position_str;

	position_str = tokens[1];
	pos_tks = ft_split(position_str, ',');
	scene->camera.center.x = str_to_double(pos_tks[0], pos_tks, &t, scene);
	scene->camera.center.y = str_to_double(pos_tks[1], pos_tks, &t, scene);
	scene->camera.center.z = str_to_double(pos_tks[2], pos_tks, &t, scene);
	free_split(pos_tks);
}

void	parse_camera(t_token t, t_scene *scene)
{
	char	**tokens;

	if (scene->num_camera == 1)
	{
		print_error("Camera already defined: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	tokens = ft_split(t.line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for camera: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(tokens, 4, t, scene);
	parse_camera_pos(scene, tokens, t);
	parse_camera_dvs(scene, tokens, t);
	parse_camera_fov(scene, tokens, t);
	free_split(tokens);
	scene->num_camera = 1;
}
