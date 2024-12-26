/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:55:52 by ansebast          #+#    #+#             */
/*   Updated: 2024/12/26 14:51:02 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
		ft_puterror("Usage: ./miniRT <file.rt>\n", 2);
	check_file(av[1]);
	printf("Hello, World!\n");
	return (0);
}