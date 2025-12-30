/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:22 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

t_error_code	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time_ms = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	return (ERROR_NONE);
}

t_error_code	philo_eat(t_philo *philo)
{
	t_error_code	error;

	if (philo->config->philo_count == 1)
	{
		take_forks(philo);
		precise_sleep_ms(philo->config->death_time_ms + 1, philo->config);
		return (ERROR_NONE);
	}
	error = take_forks(philo);
	if (error != ERROR_NONE || is_simulation_over(philo->config))
		return (error);
	error = update_meal_time(philo);
	if (error != ERROR_NONE)
		return (release_forks(philo), error);
	print_philo_action(philo, "is eating");
	precise_sleep_ms(philo->config->eat_duration_ms, philo->config);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	return (release_forks(philo));
}

t_error_code	philo_think(t_philo *philo)
{
	long	think_time;

	print_philo_action(philo, "is thinking");
	if (philo->config->philo_count % 2 != 0)
	{
		think_time = (philo->config->eat_duration_ms * 2
				- philo->config->sleep_duration_ms);
		if (think_time > 0 && think_time < 1000)
			precise_sleep_ms(think_time / 2, philo->config);
	}
	return (ERROR_NONE);
}

t_error_code	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping");
	precise_sleep_ms(philo->config->sleep_duration_ms, philo->config);
	return (ERROR_NONE);
}
