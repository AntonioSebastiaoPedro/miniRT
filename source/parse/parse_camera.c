/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:15:05 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:28:32 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	calculate_camera_vectors(t_camera *camera)
{
	double	length;
	t_vec3	dv_aux;

	dv_aux.x = 0;
	dv_aux.y = 1;
	dv_aux.z = 0;
	camera->dh.x = camera->dvs.y * dv_aux.z - camera->dvs.z * dv_aux.y;
	camera->dh.y = camera->dvs.z * dv_aux.x - camera->dvs.x * dv_aux.z;
	camera->dh.z = camera->dvs.x * dv_aux.y - camera->dvs.y * dv_aux.x;
	length = sqrt(camera->dh.x * camera->dh.x
			+ camera->dh.y * camera->dh.y
			+ camera->dh.z * camera->dh.z);
	if (length != 0)
	{
		camera->dh.x /= length;
		camera->dh.y /= length;
		camera->dh.z /= length;
	}
	camera->dv.x = camera->dh.y * camera->dvs.z - camera->dh.z * camera->dvs.y;
	camera->dv.y = camera->dh.z * camera->dvs.x - camera->dh.x * camera->dvs.z;
	camera->dv.z = camera->dh.x * camera->dvs.y - camera->dh.y * camera->dvs.x;
}

void	parse_camera_fov(t_camera *camera, char **tokens, char *line, int fd)
{
	char	*fov_str;
	t_file	file;

	file.fd = fd;
	file.line = line;
	fov_str = tokens[3];
	camera->fov = str_to_double(fov_str, NULL, tokens, &file);
	if (camera->fov < 0.0 || camera->fov > 180.0)
	{
		print_error("Invalid FOV for camera (must be in the range [0,180]): ",
			line);
		free_split(tokens);
		free_line_exit(line, fd);
	}
}

void	parse_camera_dvs(t_camera *camera, char **tokens, char *line, int fd)
{
	char	**dvs_tokens;
	double	length;
	t_file	file;

	file.fd = fd;
	file.line = line;
	dvs_tokens = ft_split(tokens[2], ',');
	camera->dvs.x = str_to_double(dvs_tokens[0], dvs_tokens, tokens, &file);
	camera->dvs.y = str_to_double(dvs_tokens[1], dvs_tokens, tokens, &file);
	camera->dvs.z = str_to_double(dvs_tokens[2], dvs_tokens, tokens, &file);
	free_split(dvs_tokens);
	if (camera->dvs.x < -1.0 || camera->dvs.x > 1.0
		|| camera->dvs.y < -1.0 || camera->dvs.y > 1.0
		|| camera->dvs.z < -1.0 || camera->dvs.z > 1.0)
	{
		print_error_camera(tokens, line, fd, 1);
	}
	length = sqrt(camera->dvs.x * camera->dvs.x
			+ camera->dvs.y * camera->dvs.y
			+ camera->dvs.z * camera->dvs.z);
	if (length == 0)
		print_error_camera(tokens, line, fd, 0);
	camera->dvs.x /= length;
	camera->dvs.y /= length;
	camera->dvs.z /= length;
}

void	parse_camera_pos(t_camera *camera, char **tokens, char *line, int fd)
{
	char	**pos_tks;
	char	*position_str;
	t_file	file;

	file.fd = fd;
	file.line = line;
	position_str = tokens[1];
	pos_tks = ft_split(position_str, ',');
	camera->center.x = str_to_double(pos_tks[0], pos_tks, tokens, &file);
	camera->center.y = str_to_double(pos_tks[1], pos_tks, tokens, &file);
	camera->center.z = str_to_double(pos_tks[2], pos_tks, tokens, &file);
	free_split(pos_tks);
}

void	parse_camera(char *line, int fd, t_scene *scene)
{
	char	**tokens;

	if (scene->num_camera == 1)
	{
		print_error("Camera already defined: ", line);
		free_line_exit(line, fd);
	}
	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for camera: ", line);
		free_line_exit(line, fd);
	}
	validate_token_number(tokens, 4, line, fd);
	parse_camera_pos(&scene->camera, tokens, line, fd);
	parse_camera_dvs(&scene->camera, tokens, line, fd);
	parse_camera_fov(&scene->camera, tokens, line, fd);
	calculate_camera_vectors(&scene->camera);
	printf("Câmera:\n");
	printf("  Posição: (%.2f, %.2f, %.2f)\n", scene->camera.center.x,
		scene->camera.center.y, scene->camera.center.z);
	printf("  Forward: (%.2f, %.2f, %.2f)\n", scene->camera.dvs.x,
		scene->camera.dvs.y, scene->camera.dvs.z);
	printf("  Right:   (%.2f, %.2f, %.2f)\n", scene->camera.dh.x,
		scene->camera.dh.y, scene->camera.dh.z);
	printf("  Up:      (%.2f, %.2f, %.2f)\n", scene->camera.dv.x,
		scene->camera.dv.y, scene->camera.dv.z);
	printf("  FOV:     %.2f graus\n", scene->camera.fov);
	free_split(tokens);
	scene->num_camera = 1;
}
