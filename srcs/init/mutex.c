/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:14 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	destroy_fork_mutexes(t_simulation *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&sim->fork_locks[i]);
		i++;
	}
}

static t_error_code	init_print_lock(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->config.print_lock, NULL) != 0)
	{
		destroy_fork_mutexes(sim, sim->config.philo_count);
		free(sim->fork_locks);
		return (ERROR_MUTEX);
	}
	return (ERROR_NONE);
}

static t_error_code	init_state_lock(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->config.sim_state_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->config.print_lock);
		destroy_fork_mutexes(sim, sim->config.philo_count);
		free(sim->fork_locks);
		return (ERROR_MUTEX);
	}
	return (ERROR_NONE);
}

static t_error_code	init_all_fork_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.philo_count)
	{
		if (pthread_mutex_init(&sim->fork_locks[i], NULL) != 0)
		{
			destroy_fork_mutexes(sim, i);
			free(sim->fork_locks);
			return (ERROR_MUTEX);
		}
		i++;
	}
	return (ERROR_NONE);
}

t_error_code	init_fork_mutexes(t_simulation *sim)
{
	t_error_code	error;

	sim->fork_locks = malloc(sizeof(pthread_mutex_t)
			* sim->config.philo_count);
	if (sim->fork_locks == NULL)
		return (ERROR_MEMORY);
	error = init_all_fork_mutexes(sim);
	if (error != ERROR_NONE)
		return (error);
	error = init_print_lock(sim);
	if (error != ERROR_NONE)
		return (error);
	error = init_state_lock(sim);
	return (error);
}
