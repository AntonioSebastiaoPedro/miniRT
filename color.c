/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 10:51:44 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_color(int fd, t_color pixel_color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * vec3_x(&pixel_color));
	g = (int)(255.999 * vec3_y(&pixel_color));
	b = (int)(255.999 * vec3_z(&pixel_color));
	dprintf(fd, "%d %d %d\n", r, g, b);
}
