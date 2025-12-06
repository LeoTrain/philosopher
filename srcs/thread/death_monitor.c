/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:21 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	check_completion(t_philo *philo, t_program *program)
{
	if (philo->shared_data->max_meals == -1)
		return (0);
	pthread_mutex_lock(philo->meal_time_mutex);
	if (philo->meal_amount_eaten == philo->shared_data->max_meals)
	{
		pthread_mutex_unlock(philo->meal_time_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_time_mutex);
	pthread_mutex_lock(&program->completion_counter_mutex);
	if (program->completion_counter_full == 1)
	{
		pthread_mutex_unlock(&program->completion_counter_mutex);
		return (1);
	}
	pthread_mutex_unlock(&program->completion_counter_mutex);
	return (0);
}

static int	check_philosopher_death(t_philo *philo, t_program *program)
{
	long	current_time;
	long	last_meal;

	if (check_completion(philo, program))
		return (1);
	pthread_mutex_lock(philo->meal_time_mutex);
	last_meal = philo->meal_time_last;
	pthread_mutex_unlock(philo->meal_time_mutex);
	current_time = get_current_time();
	if (current_time - last_meal >= philo->shared_data->time_to_die)
	{
		pthread_mutex_lock(philo->someone_died_mutex);
		if (program->someone_died == 0)
		{
			program->someone_died = 1;
			pthread_mutex_unlock(philo->someone_died_mutex);
			log_dead(philo);
			return (1);
		}
		pthread_mutex_unlock(philo->someone_died_mutex);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	int			i;
	t_program	*program;

	program = (t_program *)arg;
	while (get_current_time() < program->args.start_time)
		usleep(50);
	while (1)
	{
		i = 0;
		while (i < program->args.philosopher_amount)
		{
			if (check_philosopher_death(&program->philosophers[i], program))
				return (NULL);
			i++;
		}
		usleep(50);
	}
	return (NULL);
}
