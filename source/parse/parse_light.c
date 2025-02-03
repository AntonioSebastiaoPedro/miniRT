/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:03 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_light_position(t_scene *scene, char **tokens, t_token t)
{
	char	**pos_tokens;
	char	*position_str;

	position_str = tokens[1];
	pos_tokens = ft_split(position_str, ',');
	scene->light.position.x = str_to_double(pos_tokens[0], pos_tokens, &t,
			scene);
	scene->light.position.y = str_to_double(pos_tokens[1], pos_tokens, &t,
			scene);
	scene->light.position.z = str_to_double(pos_tokens[2], pos_tokens, &t,
			scene);
	free_split(pos_tokens);
}

void	parse_light(t_token t, t_scene *scene)
{
	char	**tokens;

	if (scene->num_light == 1)
	{
		print_error("Light already defined: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	tokens = ft_split(t.line, ' ');
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		free_split(tokens);
		print_error("Invalid format for light brightness: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(tokens, 4, t, scene);
	parse_light_position(scene, tokens, t);
	scene->light.brightness = parse_ratio(tokens, t, 0, scene);
	scene->light.color = parse_color(tokens, tokens[3], t, scene);
	free_split(tokens);
	scene->num_light = 1;
}
