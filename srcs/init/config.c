/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:12 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_error_code	parse_philo_count(char **argv, t_simulation_config *cfg)
{
	t_error_code	error;
	long			value;

	error = parse_positive_long(argv[1], &value);
	if (error != ERROR_NONE || value <= 0 || value > 200)
		return (ERROR_INVALID_ARG);
	cfg->philo_count = (int)value;
	return (ERROR_NONE);
}

static t_error_code	parse_times(char **argv, t_simulation_config *config)
{
	t_error_code	error;
	long			value;

	error = parse_positive_long(argv[2], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	config->death_time_ms = (int)value;
	error = parse_positive_long(argv[3], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	config->eat_duration_ms = (int)value;
	error = parse_positive_long(argv[4], &value);
	if (error != ERROR_NONE || value < 60)
		return (ERROR_INVALID_ARG);
	config->sleep_duration_ms = (int)value;
	return (ERROR_NONE);
}

static t_error_code	parse_meal_count(int argc, char **argv,
	t_simulation_config *config)
{
	t_error_code	error;
	long			value;

	if (argc == 6)
	{
		error = parse_positive_long(argv[5], &value);
		if (error != ERROR_NONE || value <= 0)
			return (ERROR_INVALID_ARG);
		config->required_meal_count = (int)value;
	}
	else
		config->required_meal_count = -1;
	return (ERROR_NONE);
}

t_error_code	init_simulation_config(int argc, char **argv,
	t_simulation_config *config)
{
	t_error_code	error;

	error = parse_philo_count(argv, config);
	if (error != ERROR_NONE)
		return (error);
	error = parse_times(argv, config);
	if (error != ERROR_NONE)
		return (error);
	error = parse_meal_count(argc, argv, config);
	if (error != ERROR_NONE)
		return (error);
	config->is_simulation_running = 1;
	return (ERROR_NONE);
}
