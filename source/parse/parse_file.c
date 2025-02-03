/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:03:41 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 06:26:25 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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

void	process_line(char *line, int fd, t_scene *scene)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "A", 1) == 0)
		parse_ambient_light(line, fd, scene);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		parse_camera(line, fd, scene);
	else if (ft_strncmp(&line[i], "L", 1) == 0)
		parse_light(line, fd, scene);
	else if (ft_strncmp(&line[i], "sp", 2) == 0)
		parse_sphere(line, fd, scene);
	else if (ft_strncmp(&line[i], "pl", 2) == 0)
		parse_plane(line, fd, scene);
	else if (ft_strncmp(&line[i], "cy", 2) == 0)
		parse_cylinder(line, fd, scene);
	else
	{
		print_error("Type identifier on line unknown: ", line);
		free_line_exit(line, fd, scene);
	}
}

void	parse_file(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	validate_file(file, &fd);
	init_a_c_l(scene);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strisspace(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		process_line(line, fd, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->num_camera || !scene->num_ambient_light || !scene->num_light)
	{
		print_error("The scene must contain at least camera,\
			light and ambient light\n", NULL);
		free_mlx_scene(scene, 2);
	}
}
