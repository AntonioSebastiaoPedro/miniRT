/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:03:41 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	validate_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		print_error("No such file or directory: ", file);
	if (!has_rt_extension(file))
	{
		close(*fd);
		print_error("File does not have the .rt extension: ", file);
	}
}

void	process_line(t_token t, t_scene *scene)
{
	int	i;

	i = 0;
	while (t.line[i] && ft_isspace(t.line[i]))
		i++;
	if (ft_strncmp(&t.line[i], "A", 1) == 0)
		parse_ambient_light(t, scene);
	else if (ft_strncmp(&t.line[i], "C", 1) == 0)
		parse_camera(t, scene);
	else if (ft_strncmp(&t.line[i], "L", 1) == 0)
		parse_light(t, scene);
	else if (ft_strncmp(&t.line[i], "sp", 2) == 0)
		parse_sphere(t, scene);
	else if (ft_strncmp(&t.line[i], "pl", 2) == 0)
		parse_plane(t, scene);
	else if (ft_strncmp(&t.line[i], "cy", 2) == 0)
		parse_cylinder(t, scene);
	else
	{
		print_error("Type identifier on line unknown: ", t.line);
		free_line_exit(t.line, t.fd, scene);
	}
}

void	parse_file(char *file, t_scene *scene)
{
	t_token	t;

	validate_file(file, &t.fd);
	init_a_c_l(scene);
	t.line = get_next_line(t.fd);
	while (t.line != NULL)
	{
		if (ft_strisspace(t.line))
		{
			free(t.line);
			t.line = get_next_line(t.fd);
			continue ;
		}
		process_line(t, scene);
		free(t.line);
		t.line = get_next_line(t.fd);
	}
	close(t.fd);
	if (!scene->num_camera || !scene->num_ambient_light || !scene->num_light)
	{
		print_error("The scene must contain at least camera,\
			light and ambient light\n", NULL);
		free_mlx_scene(scene, 2);
	}
}
