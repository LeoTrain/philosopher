/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:16 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	assign_forks(t_philo *philo, t_simulation *sim, int i)
{
	philo->fork_pair.left_fork = &sim->fork_locks[i];
	philo->fork_pair.right_fork = &sim->fork_locks[(i + 1)
		% sim->config.philo_count];
}

static void	init_single_philo(t_philo *philo, t_simulation *sim, int i)
{
	philo->id = i + 1;
	philo->state = STATE_THINKING;
	philo->meal_count = 0;
	philo->last_meal_time_ms = 0;
	philo->config = &sim->config;
	assign_forks(philo, sim, i);
}

static t_error_code	init_philo_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.philo_count)
	{
		if (pthread_mutex_init(&sim->philos[i].meal_lock, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->philos[i].meal_lock);
			free(sim->philos);
			return (ERROR_MUTEX);
		}
		i++;
	}
	return (ERROR_NONE);
}

t_error_code	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->config.philo_count);
	if (sim->philos == NULL)
		return (ERROR_MEMORY);
	i = 0;
	while (i < sim->config.philo_count)
	{
		init_single_philo(&sim->philos[i], sim, i);
		i++;
	}
	return (init_philo_mutexes(sim));
}
