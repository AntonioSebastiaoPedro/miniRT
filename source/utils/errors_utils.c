/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:06:12 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_error(char *error_message, char *param)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	if (param != NULL)
		ft_putstr_fd(param, 2);
}

void	print_error_camera(char **tokens, t_token t, int is_dvs,
	t_scene *scene)
{
	if (is_dvs)
	{
		print_error("Invalid camera orientation vector "
			"(must be in the range [-1,1]: ", t.line);
	}
	else
	{
		print_error("Invalid camera orientation vector "
			"(coordinates are zeros): ", t.line);
	}
	free_split(tokens);
	free_line_exit(t.line, t.fd, scene);
}

void	print_error_plane(char **tokens, t_token t, int is_range,
	t_scene *scene)
{
	if (is_range)
	{
		print_error("Invalid plane orientation normal vector "
			"(must be in the range [-1,1]: ", t.line);
	}
	else
	{
		print_error("Invalid plane orientation normal vector "
			"(coordinates are zeros): ", t.line);
	}
	free_split(tokens);
	free_line_exit(t.line, t.fd, scene);
}

void	print_error_cylinder(char **tokens, t_token t, int is_range,
	t_scene *scene)
{
	if (is_range)
	{
		print_error("Invalid cylinder orientation vector of axis "
			"(must be in the range [-1,1]: ", t.line);
	}
	else
	{
		print_error("Invalid cylinder orientation vector of axis "
			"(coordinates are zeros): ", t.line);
	}
	free_split(tokens);
	free_line_exit(t.line, t.fd, scene);
}
