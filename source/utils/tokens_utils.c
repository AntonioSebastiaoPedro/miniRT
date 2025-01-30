/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:03:34 by ateca             #+#    #+#             */
/*   Updated: 2025/01/29 19:04:56 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	free_split(char **tokens)
{
	size_t	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	validate_token_number(char **tokens, int expe_count, char *line, int fd)
{
	int		count;
	char	*message;

	count = 0;
	message = "Incorrect number of parameters in line: "
		"%sExpected %d, but found %d.\n";
	while (tokens[count] && !ft_strisspace(tokens[count]))
	{
		count++;
	}
	if (count != expe_count)
	{
		ft_putstr_fd("Error\n", 2);
		printf(message, line, expe_count, count);
		free_split(tokens);
		free_line_exit(line, fd);
	}
}
