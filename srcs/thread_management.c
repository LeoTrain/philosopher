/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:58 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_error_code	init_start_time(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->config.sim_start_time_ms = get_time_ms();
	if (sim->config.sim_start_time_ms == 0)
		return (ERROR_MEMORY);
	while (i < sim->config.philo_count)
	{
		sim->philos[i].last_meal_time_ms = sim->config.sim_start_time_ms;
		i++;
	}
	return (ERROR_NONE);
}

t_error_code	create_philo_threads(t_simulation *sim)
{
	int				i;
	t_error_code	error;

	sim->philo_threads = malloc(sizeof(pthread_t) * sim->config.philo_count);
	if (sim->philo_threads == NULL)
		return (ERROR_MEMORY);
	error = init_start_time(sim);
	if (error != ERROR_NONE)
		return (free(sim->philo_threads), error);
	i = 0;
	while (i < sim->config.philo_count)
	{
		if (pthread_create(&sim->philo_threads[i], NULL,
				philo_lifecycle, (void *)&sim->philos[i]) != 0)
		{
			stop_simulation(&sim->config);
			while (--i >= 0)
				pthread_join(sim->philo_threads[i], NULL);
			return (free(sim->philo_threads), ERROR_THREAD);
		}
		i++;
	}
	return (ERROR_NONE);
}

t_error_code	create_death_monitor(t_simulation *sim)
{
	if (pthread_create(&sim->death_monitor.monitor_thread, NULL,
			death_monitor_loop, (void *)sim) != 0)
		return (ERROR_THREAD);
	return (ERROR_NONE);
}

t_error_code	join_all_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.philo_count)
	{
		if (pthread_join(sim->philo_threads[i], NULL))
			return (ERROR_THREAD);
		i++;
	}
	if (pthread_join(sim->death_monitor.monitor_thread, NULL) != 0)
		return (ERROR_THREAD);
	return (ERROR_NONE);
}
