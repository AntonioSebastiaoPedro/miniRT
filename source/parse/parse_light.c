/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:03 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:32:08 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_light_position(t_light *light, char **tokens, char *line, int fd)
{
	char	**pos_tokens;
	char	*position_str;
	t_file	file;

	file.fd = fd;
	file.line = line;
	position_str = tokens[1];
	pos_tokens = ft_split(position_str, ',');
	light->position.x = str_to_double(pos_tokens[0], pos_tokens, tokens, &file);
	light->position.y = str_to_double(pos_tokens[1], pos_tokens, tokens, &file);
	light->position.z = str_to_double(pos_tokens[2], pos_tokens, tokens, &file);
	free_split(pos_tokens);
}

void	parse_light(char *line, int fd, t_scene	*scene)
{
	char	**tokens;

	if (scene->num_light == 1)
	{
		print_error("Light already defined: ", line);
		free_line_exit(line, fd);
	}
	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for light brightness: ", line);
		free_line_exit(line, fd);
	}
	validate_token_number(tokens, 4, line, fd);
	parse_light_position(&scene->light, tokens, line, fd);
	scene->light.brightness = parse_ratio(tokens, line, fd, 0);
	scene->light.color = parse_color(tokens, tokens[3], line, fd);
	// printf("Luz: posição=(%.2f, %.2f, %.2f), intensidade=%.2f,"
	// 	"cor=(%d, %d, %d)\n", scene->light.position.x, scene->light.position.y,
	// 	scene->light.position.z, scene->light.brightness, scene->light.color.x,
	// 	scene->light.color.y, scene->light.color.z);
	free_split(tokens);
	scene->num_light = 1;
}
