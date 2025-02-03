/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:35:30 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 17:38:28 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	parse_ambient_light(t_token t, t_scene *scene)
{
	if (scene->num_ambient_light == 1)
	{
		print_error("Ambient light already defined: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	t.tokens = ft_split(t.line, ' ');
	if (!t.tokens[1] || !t.tokens[2])
	{
		free_split(t.tokens);
		print_error("Invalid format for ambient light: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validate_token_number(t.tokens, 3, t, scene);
	scene->ambient_light.intensity = parse_ratio(t.tokens, t, 1,
			scene);
	scene->ambient_light.color = parse_color(t.tokens, t.tokens[2], t, scene);
	free_split(t.tokens);
	scene->num_ambient_light = 1;
}
