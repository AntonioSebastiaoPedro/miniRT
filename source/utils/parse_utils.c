/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:06:11 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:18:43 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

double	parse_ratio(char **tokens, t_token t, int is_ambient_light,
		t_scene *scene)
{
	double	ratio;
	char	*token_str;

	if (is_ambient_light)
		token_str = tokens[1];
	else
		token_str = tokens[2];
	ratio = str_to_double(token_str, NULL, &t, scene);
	if (ratio < 0.0 || ratio > 1.0)
	{
		if (is_ambient_light)
		{
			print_error("Invalid ratio value for ambient light: "
				"(must be in the range [0.0,1.0]): ", t.line);
		}
		else
			print_error("Invalid ratio value for light brightness: "
				"(must be in the range [0.0,1.0]): ", t.line);
		free_split(tokens);
		free_line_exit(t.line, t.fd, scene);
	}
	return (ratio);
}

double	parse_diameter(char *token, t_token t, t_scene *scene)
{
	char	*str_diameter;
	double	diameter;

	str_diameter = token;
	diameter = str_to_double(str_diameter, NULL, &t, scene);
	return (diameter);
}

void	validated_color_value(char **colors, char **tokens, t_token t,
		t_scene *scene)
{
	char	*color_value;

	color_value = NULL;
	if (!ft_isnumber(colors[0]))
		color_value = colors[0];
	else if (!ft_isnumber(colors[1]))
		color_value = colors[1];
	else if (!ft_isnumber(colors[2]))
		color_value = colors[2];
	if (color_value != NULL)
	{
		print_error("Invalid color value: ", t.line);
		ft_putstr_fd("Value: ", 2);
		ft_putstr_fd(color_value, 2);
		if (color_value[ft_strlen(color_value) - 1] != '\n')
			ft_putstr_fd("\n", 2);
		free_split(colors);
		free_split(tokens);
		free_line_exit(t.line, t.fd, scene);
	}
}

t_color	parse_color(char **tokens, char *token, t_token t, t_scene *scene)
{
	t_color	c;
	char	**color_tokens;

	color_tokens = ft_split(token, ',');
	if (!color_tokens[0] || !color_tokens[1] || !color_tokens[2])
	{
		free_split(tokens);
		free_split(color_tokens);
		print_error("Invalid color format: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	validated_color_value(color_tokens, tokens, t, scene);
	c.x = ft_atoi(color_tokens[0]);
	c.y = ft_atoi(color_tokens[1]);
	c.z = ft_atoi(color_tokens[2]);
	if (c.x < 0 || c.x > 255 || c.y < 0 || c.y > 255 || c.z < 0 || c.z > 255)
	{
		free_split(tokens);
		free_split(color_tokens);
		print_error("Color values out of range "
			"(must be in the range [0-255]): ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
	free_split(color_tokens);
	return (c);
}
