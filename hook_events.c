/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:02:00 by ansebast          #+#    #+#             */
/*   Updated: 2025/02/02 09:46:05 by ansebast         ###   ########.fr       */
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
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.center = vec3_add(scene->camera.center,
				vec3_scalar_div(translation, 3));
	}
	else if (scene->type_selected_object == LIGHT)
	{
		scene->light.position = vec3_add(scene->light.position,
				vec3_scalar_div(translation, 2));
	}
}

void	resize_width(t_scene *scene, double value)
{
	t_sphere	*sp;
	t_cylinder	*cy;

	if (scene->type_selected_object == SPHERE)
	{
		sp = (t_sphere *)scene->selected_object;
		sp->diameter = fmax(1, sp->diameter + value);
		sp->radius = sp->diameter / 2;
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->diameter = fmax(1, cy->diameter + value);
		cy->radius = cy->diameter / 2;
	}
}

void	rotate_x_object(t_scene *scene, double angle)
{
	t_plane		*pl;
	t_cylinder	*cy;

	if (scene->type_selected_object == PLANE)
	{
		pl = (t_plane *)scene->selected_object;
		pl->normal = vec3_unit(vec3_rotate_x(pl->normal, angle));
	}
	else if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->normal = vec3_unit(vec3_rotate_x(cy->normal, angle));
	}
	else if (scene->type_selected_object == CAMERA)
	{
		scene->camera.dvs = vec3_unit(vec3_rotate_x(scene->camera.dvs, angle));
		camera_init(&scene->camera, &scene->viewport);
	}
}

void	resize_height(t_scene *scene, double value)
{
	t_cylinder	*cy;

	if (scene->type_selected_object == CYLINDER)
	{
		cy = (t_cylinder *)scene->selected_object;
		cy->height = fmax(1, cy->height + value);
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
	else if (keycode == 97)
		resize_width(scene, 1);
	else if (keycode == 100)
		resize_width(scene, -1);
	else if (keycode == 119)
		resize_height(scene, 1);
	else if (keycode == 115)
		resize_height(scene, -1);
	else if (keycode == 99)
		scene->type_selected_object = CAMERA;
	else if (keycode == 108)
		scene->type_selected_object = LIGHT;
	else if (keycode == 105)
		rotate_x_object(scene, -PI / 20);
	else if (keycode == 111)
		rotate_x_object(scene, PI / 20);
	update_render(scene);
}

int	ft_hand_hook(int keycode, t_scene *scene)
{
	printf("Code %d\n", keycode);
	if (keycode == 65307)
		ft_close(scene);
	if ((keycode >= 65361 && keycode <= 65364) || keycode == 65438
		|| keycode == 65436 || keycode == 97 || keycode == 100 || keycode == 119
		|| keycode == 115 || keycode == 99 || keycode == 108 || keycode == 105
		|| keycode == 111)
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
