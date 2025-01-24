/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:00:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/24 00:52:29 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "ray.h"
# include "vec3.h"

typedef t_vec3	t_color;

void			write_color(int fd, t_color pixel_color);
t_color			ray_color(t_ray *r, t_hittable **objects);
t_color			color(double r, double g, double b);

#endif
