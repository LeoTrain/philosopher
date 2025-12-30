/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:49 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	cleanup_philo_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.philo_count)
	{
		pthread_mutex_destroy(&sim->philos[i].meal_lock);
		i++;
	}
	free(sim->philos);
}

static void	cleanup_fork_mutexes(t_simulation *sim)
{
	int	i;

	pthread_mutex_destroy(&sim->config.sim_state_lock);
	pthread_mutex_destroy(&sim->config.print_lock);
	i = 0;
	while (i < sim->config.philo_count)
	{
		pthread_mutex_destroy(&sim->fork_locks[i]);
		i++;
	}
	free(sim->fork_locks);
}

void	cleanup_simulation(t_simulation *sim, int init_level)
{
	if (init_level >= 5)
		join_all_threads(sim);
	if (init_level >= 4 && sim->philo_threads)
		free(sim->philo_threads);
	if (init_level >= 3 && sim->philos)
		cleanup_philo_mutexes(sim);
	if (init_level >= 2 && sim->fork_locks)
		cleanup_fork_mutexes(sim);
}
