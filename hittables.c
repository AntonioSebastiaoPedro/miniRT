/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:35:12 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/27 23:48:46 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_closest_object(double *closest, bool *hit_anything, t_hit *hit,
		t_hit hit_temp)
{
	if (hit_temp.t < *closest)
	{
		*hit = hit_temp;
		*hit_anything = true;
		*closest = hit_temp.t;
	}
}

bool	is_hit(t_hittable **list, t_ray *r, t_ray_bounds *bounds, t_hit *hit)
{
	t_hit		hit_temp;
	bool		hit_anything;
	double		closest;
	t_hittable	*curr;

	closest = bounds->t_max;
	hit_anything = false;
	curr = (*list);
	while (curr)
	{
		if (curr->type == 0)
		{
			if (hit_sphere(curr->data, r, create_bounds(bounds->t_min, closest),
					&hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		}
		if (curr->type == 1)
		{
			if (hit_plane(curr->data, r, &hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		}
		if (curr->type == 2)
		{
			if (hit_cylinder(curr->data, r, create_bounds(bounds->t_min,
						closest), &hit_temp))
				update_closest_object(&closest, &hit_anything, hit, hit_temp);
		}
		curr = curr->next;
	}
	return (hit_anything);
}

void	add_to_hittable_list(t_hittable **list, int type, void *data)
{
	t_hittable	*new_node;

	new_node = hittable_new(type, data);
	hittable_add_back(list, new_node);
}

t_hittable	*hittable_new(int type, void *data)
{
	t_hittable	*node;

	node = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = data;
	node->next = NULL;
	return (node);
}

void	hittable_add_back(t_hittable **lst, t_hittable *new)
{
	t_hittable	*last;

	if (lst && *lst)
	{
		last = hittable_last(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_hittable	*hittable_last(t_hittable *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
