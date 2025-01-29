/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:35:30 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:23:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_ambient_light(char *line, int fd, t_scene	*scene)
{
	char	**tokens;

	if (scene->num_ambient_light == 1)
	{
		print_error("Ambient light already defined: ", line);
		free_line_exit(line, fd);
	}
	tokens = ft_split(line, ' ');
	if (!tokens[1] || !tokens[2])
	{
		free_split(tokens);
		print_error("Invalid format for ambient light: ", line);
		free_line_exit(line, fd);
	}
	validate_token_number(tokens, 3, line, fd);
	scene->ambient_light.intensity = parse_ratio(tokens, line, fd, 1);
	scene->ambient_light.color = parse_color(tokens, tokens[2], line, fd);
	// printf("Luz Ambiente: intensidade=%.2f, cor=(%d, %d, %d)\n",
	// 	scene->ambient_light.intensity, scene->ambient_light.color.x,
	// 	scene->ambient_light.color.y, scene->ambient_light.color.z);
	free_split(tokens);
	scene->num_ambient_light = 1;
}
