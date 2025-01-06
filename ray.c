/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:06:20 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/06 17:34:54 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

// Função para criar um raio
t_ray	ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

// Função para obter a origem do raio
t_vec3	ray_origin(const t_ray *r)
{
	return (r->orig);
}

// Função para obter a direção do raio
t_vec3	ray_direction(const t_ray *r)
{
	return (r->dir);
}

// Função para calcular um ponto no raio dado um valor de t
t_vec3	ray_at(const t_ray *r, double t)
{
	return (vec3_add(r->orig, vec3_scalar_mul(r->dir, t)));
}

t_ray	ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	r;

	r.orig = origin;   // Define a origem
	r.dir = direction; // Define a direção
	return (r);
}
