/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 07:42:43 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 07:50:19 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	free_scene(t_scene *scene)
{
	void	*current;

	while (scene->object_list)
	{
		current = scene->object_list->next;
		free(scene->object_list->data);
		free(scene->object_list);
		scene->object_list = current;
	}
}
