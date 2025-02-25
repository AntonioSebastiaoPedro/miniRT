/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:40:19 by ateca             #+#    #+#             */
/*   Updated: 2025/02/03 18:47:20 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_a_c_l(t_scene *scene)
{
	scene->num_light = 0;
	scene->num_camera = 0;
	scene->num_ambient_light = 0;
	scene->num_spheres = 0;
	scene->num_planes = 0;
	scene->num_cylinders = 0;
}

int	has_rt_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot && ft_strcmp(dot, ".rt") == 0)
		return (1);
	return (0);
}

double	str_to_double(char *str, char **tks_value, t_token *t, t_scene *scene)
{
	char	*endptr;
	double	value;

	value = ft_strtod(str, &endptr);
	if (*endptr != '\0' && endptr[0] != '\n' && !ft_strisspace(endptr))
	{
		print_error("Invalid value to convert to double: ", t->line);
		ft_putstr_fd("Value: ", 2);
		ft_putstr_fd(str, 2);
		if (str[ft_strlen(str) - 1] != '\n')
			ft_putstr_fd("\n", 2);
		free_split(tks_value);
		free_split(t->tokens);
		free_line_exit(t->line, t->fd, scene);
	}
	return (value);
}

void	free_line_exit(char *line_current, int fd, t_scene *scene)
{
	char	*line;

	free(line_current);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free_mlx_scene(scene, EXIT_FAILURE);
}
