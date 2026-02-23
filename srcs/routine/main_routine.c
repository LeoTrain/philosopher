/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:16 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	is_simulation_complete(t_thread_data *thread_data)
{
	int	full;

	pthread_mutex_lock(thread_data->philo->completion_counter_mutex);
	full = thread_data->program->completion_counter_full;
	pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
	return (full);
}

static int	process_eating_cycle(t_thread_data *thread_data)
{
	if (someone_died(thread_data) == 1)
		return (1);
	lock_mutexes(thread_data);
	if (someone_died(thread_data) == 1 || is_simulation_complete(thread_data))
		return (unlock_mutexes(thread_data), 1);
	pthread_mutex_lock(thread_data->philo->meal_time_mutex);
	thread_data->philo->meal_time_last = get_current_time();
	pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
	if (philo_eat(thread_data))
		return (unlock_mutexes(thread_data), 1);
	pthread_mutex_lock(thread_data->philo->meal_time_mutex);
	thread_data->philo->meal_amount_eaten++;
	pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
	if (check_meal_completion(thread_data))
		return (unlock_mutexes(thread_data), 1);
	unlock_mutexes(thread_data);
	return (0);
}

void	*philosophers_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	if (thread_data->philo->shared_data->philosopher_amount == 1)
		return (handle_single_philosopher(thread_data));
	while (get_current_time() < thread_data->program->args.start_time)
		usleep(50);
	if (is_delayed_philo(thread_data->philo))
		ft_usleep(thread_data->philo->shared_data->time_to_eat / 2,
			thread_data);
	while (1)
	{
		if (process_eating_cycle(thread_data))
			return (NULL);
		if (philo_think(thread_data))
			return (NULL);
		if (philo_sleep(thread_data))
			return (NULL);
	}
	return (NULL);
}
