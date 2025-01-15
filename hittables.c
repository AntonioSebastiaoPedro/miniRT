/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:35:12 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/14 18:49:57 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hittable_list	create_hittable_list(size_t initial_capacity)
{
	t_hittable_list	list;

	list.objects = ft_calloc(initial_capacity, sizeof(t_hittable *));
	list.size = 0;
	list.capacity = initial_capacity;
	return (list);
}

bool	is_hit(t_hittable_list *list, t_ray *r, double ray_tmin,
		double ray_tmax, t_hit *hit)
{
	t_hit	hit_temp;
	bool	hit_anything;
	double	closest_so_far;
	size_t	i;

	i = 0;
	closest_so_far = ray_tmax;
	hit_anything = false;
	while (i < list->size)
	{
		if (hit_sphere(list->objects[i], r, ray_tmin, closest_so_far,
				&hit_temp))
		{
			hit_anything = true;
			closest_so_far = hit_temp.t;
			*hit = hit_temp;
		}
		i++;
	}
	return (hit_anything);
}

void	add_hittable(t_hittable_list *list, t_hittable *object)
{
	if (list->size == list->capacity)
	{
		list->capacity *= 2;
		list->objects = realloc(list->objects, list->capacity
				* sizeof(t_hittable *));
	}
	list->objects[list->size++] = object;
}
