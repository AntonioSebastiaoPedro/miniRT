/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:30:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/02 08:27:16 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "minirt.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}			t_vec3;

t_vec3		vec3(double e0, double e1, double e2);
t_vec3		vec3_zero(void);
t_vec3		vec3_neg(t_vec3 v);
t_vec3		vec3_add(t_vec3 u, t_vec3 v);
t_vec3		vec3_sub(t_vec3 u, t_vec3 v);
t_vec3		vec3_mul(t_vec3 u, t_vec3 v);
t_vec3		vec3_scalar_mul(t_vec3 v, double t);
t_vec3		vec3_scalar_div(t_vec3 v, double t);
t_vec3		vec3_cross(t_vec3 u, t_vec3 v);
t_vec3		vec3_unit(t_vec3 v);
t_vec3		vec3_rotate_x(t_vec3 v, double angle);
t_vec3		vec3_rotate_y(t_vec3 v, double angle);
t_vec3		vec3_rotate_z(t_vec3 v, double angle);
double		vec3_dot(t_vec3 u, t_vec3 v);
double		vec3_length(t_vec3 v);
double		vec3_length_squared(t_vec3 v);

#endif
