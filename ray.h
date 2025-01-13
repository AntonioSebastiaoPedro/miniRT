/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:04:05 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/13 18:20:12 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"

typedef struct s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}			t_ray;

t_ray		ray(t_vec3 origin, t_vec3 direction);
t_vec3		ray_point(const t_ray *r, double t);

#endif
