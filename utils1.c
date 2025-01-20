/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:45:23 by ansebast          #+#    #+#             */
/*   Updated: 2025/01/17 18:24:29 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "time.h"

double	rnd(void)
{
	srand(time(NULL));
	return ((double)rand() / (double)RAND_MAX);
}
double	random_double(double min, double max)
{
	if (min == 0.0 && max == 0.0)
		return (rnd());
	else
	{
		srand(time(NULL));
		return (min + (double)rand() / ((double)RAND_MAX / (max - min)));
	}
}

double	linear_to_gama(double linear_component)
{
	if (linear_component > 0.0)
		return (sqrt(linear_component));
	return (0.0);
}

double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
