/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:54 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	announce_death(t_simulation *sim, int i, long current_time)
{
	pthread_mutex_lock(&sim->config.sim_state_lock);
	sim->config.is_simulation_running = 0;
	pthread_mutex_unlock(&sim->config.sim_state_lock);
	pthread_mutex_lock(&sim->config.print_lock);
	printf("%ld %d died\n",
		current_time - sim->config.sim_start_time_ms, sim->philos[i].id);
	pthread_mutex_unlock(&sim->config.print_lock);
}

static int	check_philo_death(t_simulation *sim, int i)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&sim->philos[i].meal_lock);
	current_time = get_time_ms();
	time_since_meal = current_time - sim->philos[i].last_meal_time_ms;
	pthread_mutex_unlock(&sim->philos[i].meal_lock);
	if (time_since_meal >= sim->config.death_time_ms)
	{
		announce_death(sim, i, current_time);
		return (1);
	}
	return (0);
}

int	check_meal_goal_reached(t_simulation *sim)
{
	int	i;
	int	all_done;

	if (sim->config.required_meal_count == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < sim->config.philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_lock);
		if (sim->philos[i].meal_count < sim->config.required_meal_count)
			all_done = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_lock);
		if (!all_done)
			break ;
		i++;
	}
	return (all_done);
}

void	*death_monitor_loop(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (i < sim->config.philo_count)
		{
			if (check_philo_death(sim, i))
				return (NULL);
			i++;
		}
		if (check_meal_goal_reached(sim))
		{
			stop_simulation(&sim->config);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
