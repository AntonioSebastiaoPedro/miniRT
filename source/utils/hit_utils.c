/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:50:35 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/03 18:49:31 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

void	set_hit_object(t_hit *hit, double t, t_vec3 hit_point, void *object)
{
	hit->t = t;
	hit->hit_point = hit_point;
	hit->object = object;
}
