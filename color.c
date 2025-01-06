/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 17:34:41 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 ray_color(const t_ray *r) {
    // Calcula a direção unitarizada do raio
    t_vec3 unit_direction = unit_vector(r->dir);

    // Calcula o fator de interpolação baseado no componente Y da direção
    double a = 0.5 * (vec3_y(&unit_direction) + 1.0);

    // Realiza a interpolação linear entre branco (1.0, 1.0, 1.0) e azul claro (0.5, 0.7, 1.0)
    t_vec3 white = vec3(1.0, 1.0, 1.0);
    t_vec3 blue = vec3(0.5, 0.7, 1.0);
    return vec3_add(vec3_scalar_mul(white, (1.0 - a)), vec3_scalar_mul(blue, a));
}

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
