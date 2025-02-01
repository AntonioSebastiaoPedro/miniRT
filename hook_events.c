/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:02:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/01 11:23:15 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_render(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	render_image(&scene->camera, &scene->object_list, scene, false);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0, 0);
}

void	select_object(t_scene *scene, t_ray *ray)
{
	t_hit			hit_temp;
	t_ray_bounds	limits;

	limits = create_bounds(1e-64, __DBL_MAX__);
	if (is_hit(&scene->object_list, ray, &limits, &hit_temp))
	{
		if (hit_temp.type == SPHERE)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = SPHERE;
		}
		else if (hit_temp.type == PLANE)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = PLANE;
		}
		else if (hit_temp.type == CYLINDER)
		{
			scene->selected_object = hit_temp.object;
			scene->type_selected_object = CYLINDER;
		}
	}
}

t_ray	create_ray_from_mouse(int x, int y, t_camera *camera)
{
	t_color	pixel_pos;
	t_vec3	ray_dir;
	t_ray	r;

	pixel_pos = vec3_add(vec3_add(camera->pixel00_loc,
				vec3_scalar_mul(camera->pixel_delta_u, x)),
			vec3_scalar_mul(camera->pixel_delta_v, y));
	ray_dir = vec3_unit(vec3_sub(pixel_pos, camera->center));
	r = ray(camera->center, ray_dir);
	return (r);
}

int	mouse_hook(int keycode, int x, int y, t_scene *scene)
{
	t_ray	ray;

	if (keycode == 1)
	{
		ray = create_ray_from_mouse(x, y, &scene->camera);
		select_object(scene, &ray);
		printf("%d\n", scene->type_selected_object);
	}
	return (0);
}

void	translate_object(t_scene *scene, t_vec3 translation)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (scene->type_selected_object == SPHERE)
	{
		sp = (t_sphere *)scene->selected_object;
		sp->center = vec3_add(sp->center, translation);
	}
	else if (scene->type_selected_object == PLANE)
	{
		pl = (t_plane *)scene->selected_object;
		pl->point = vec3_add(pl->point, translation);
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->center = vec3_add(cy->center, translation);
	}
}

void	get_keycode(int keycode, t_scene *scene)
{
	if (keycode == 65361)
		translate_object(scene, vec3(-1, 0, 0));
	else if (keycode == 65363)
		translate_object(scene, vec3(1, 0, 0));
	else if (keycode == 65362)
		translate_object(scene, vec3(0, 1, 0));
	else if (keycode == 65364)
		translate_object(scene, vec3(0, -1, 0));
	else if (keycode == 65438)
		translate_object(scene, vec3(0, 0, -1));
	else if (keycode == 65436)
		translate_object(scene, vec3(0, 0, 1));
	update_render(scene);
}

int	ft_hand_hook(int keycode, t_scene *scene)
{
	printf("Code %d\n", keycode);
	if ((keycode >= 65361 && keycode <= 65364) || keycode == 65438
		|| keycode == 65436)
		get_keycode(keycode, scene);
	if (keycode == 114)
	{
		mlx_destroy_image(scene->mlx, scene->img.img);
		scene->img.img = mlx_new_image(scene->mlx, WIN_WIDTH, WIN_HEIGHT);
		scene->img.addr = mlx_get_data_addr(scene->img.img,
				&scene->img.bits_per_pixel, &scene->img.line_length,
				&scene->img.endian);
		free_scene(scene);
		scene->selected_object = NULL;
		scene->type_selected_object = -1;
		parse_file(scene->map, scene);
		camera_init(&scene->camera, &scene->viewport);
		render_image(&scene->camera, &scene->object_list, scene, true);
		mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->img.img, 0,
			0);
	}
	return (0);
}
