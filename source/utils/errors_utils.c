/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:06:12 by ateca             #+#    #+#             */
/*   Updated: 2025/02/02 19:37:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	print_error(char *error_message, char *param)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_message, 2);
	if (param != NULL)
		ft_putstr_fd(param, 2);
}

void	print_error_camera(char **tokens, char *line, int fd, int is_dvs, t_scene *scene)
{
	if (is_dvs)
	{
		print_error("Invalid camera orientation vector "
			"(must be in the range [-1,1]: ", line);
	}
	else
	{
		print_error("Invalid camera orientation vector "
			"(coordinates are zeros): ", line);
	}
	free_split(tokens);
	free_line_exit(line, fd, scene);
}

void	print_error_plane(char **tokens, char *line, int fd, int is_range, t_scene *scene)
{
	if (is_range)
	{
		print_error("Invalid plane orientation normal vector "
			"(must be in the range [-1,1]: ", line);
	}
	else
	{
		print_error("Invalid plane orientation normal vector "
			"(coordinates are zeros): ", line);
	}
	free_split(tokens);
	free_line_exit(line, fd, scene);
}

void	print_error_cylinder(char **tokens, char *line, int fd, int is_range, t_scene *scene)
{
	if (is_range)
	{
		print_error("Invalid cylinder orientation vector of axis "
			"(must be in the range [-1,1]: ", line);
	}
	else
	{
		print_error("Invalid cylinder orientation vector of axis "
			"(coordinates are zeros): ", line);
	}
	free_split(tokens);
	free_line_exit(line, fd, scene);
}
