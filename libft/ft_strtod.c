/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateca <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:33:07 by ateca             #+#    #+#             */
/*   Updated: 2025/01/20 10:33:10 by ateca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

double	parse_fraction(const char **p);
double	parse_exponent(const char **p);
void	skip_whitespace(const char **p);
int		parse_sign(const char **p);

double	ft_strtod(const char *str, char **endptr)
{
	const char	*p;
	double		result;
	int			sign;

	p = str;
	result = 0.0;
	skip_whitespace(&p);
	sign = parse_sign(&p);
	while (ft_isdigit((unsigned char)*p))
	{
		result = result * 10.0 + (*p - '0');
		p++;
	}
	result += parse_fraction(&p);
	result *= pow(10, parse_exponent(&p));
	result *= sign;
	if (endptr)
	{
		*endptr = (char *)p;
	}
	return (result);
}

void	skip_whitespace(const char **p)
{
	while (ft_isspace((unsigned char)**p))
	{
		(*p)++;
	}
}

int	parse_sign(const char **p)
{
	int	sign;

	sign = 1;
	if (**p == '-')
	{
		sign = -1;
		(*p)++;
	}
	else if (**p == '+')
	{
		(*p)++;
	}
	return (sign);
}

double	parse_fraction(const char **p)
{
	double	fraction;
	double	factor;

	fraction = 0.0;
	factor = 1.0;
	if (**p == '.')
	{
		(*p)++;
		while (ft_isdigit((unsigned char)**p))
		{
			factor /= 10.0;
			fraction += (**p - '0') * factor;
			(*p)++;
		}
	}
	return (fraction);
}

double	parse_exponent(const char **p)
{
	int	exp_sign;
	int	exponent_value;

	exp_sign = 1;
	exponent_value = 0;
	if (**p == 'e' || **p == 'E')
	{
		(*p)++;
		if (**p == '-')
		{
			exp_sign = -1;
			(*p)++;
		}
		else if (**p == '+')
		{
			(*p)++;
		}
		while (ft_isdigit((unsigned char)**p))
		{
			exponent_value = exponent_value * 10 + (**p - '0');
			(*p)++;
		}
	}
	return (exp_sign * exponent_value);
}
