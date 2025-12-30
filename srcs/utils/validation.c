/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:08 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_error_code	str_is_all_digits(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (ERROR_INVALID_ARG);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR_INVALID_ARG);
		i++;
	}
	return (ERROR_NONE);
}

t_error_code	parse_positive_long(const char *str, long *out)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERROR_INVALID_ARG);
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (ERROR_INVALID_ARG);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	*out = result;
	return (ERROR_NONE);
}

t_error_code	validate_all_args(int argc, char **argv)
{
	int				i;
	t_error_code	error;

	i = 1;
	while (i < argc)
	{
		error = str_is_all_digits(argv[i]);
		if (error != ERROR_NONE)
			return (error);
		i++;
	}
	return (ERROR_NONE);
}
