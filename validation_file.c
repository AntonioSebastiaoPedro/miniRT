/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:28:43 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/26 14:52:53 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_file(char *path_file)
{
	char	*extension;
	int		len;

	len = len_line_file(path_file);
	extension = ft_strrchr(path_file, '.');
	if (!extension || ft_strncmp(extension, ".rt", 4))
		ft_puterror("Invalid file.\n", 1);
	if (len == -1)
		ft_puterror("Error opening file.\n", 1);
	if (len == 0)
		ft_puterror("The file is empty.\n", 1);
}

int	len_line_file(char *path_file)
{
	int fd;
	int len;
	char *line;

	fd = open(path_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	len = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		len++;
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}
