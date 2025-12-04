#include "../../includes/philo.h"

static int	process_eating_cycle(t_thread_data *thread_data)
{
	if (someone_died(thread_data) == 1)
		return (1);
	pthread_mutex_lock(thread_data->philo->meal_time_mutex);
	thread_data->philo->is_eating = 1;
	pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
	lock_mutexes(thread_data->philo);
	if (someone_died(thread_data) == 1)
	{
		pthread_mutex_lock(thread_data->philo->meal_time_mutex);
		thread_data->philo->is_eating = 0;
		pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
		return (unlock_mutexes(thread_data->philo), 1);
	}
	pthread_mutex_lock(thread_data->philo->meal_time_mutex);
	thread_data->philo->meal_time_last = get_current_time();
	pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
	if (philo_eat(thread_data))
	{
		pthread_mutex_lock(thread_data->philo->meal_time_mutex);
		thread_data->philo->is_eating = 0;
		pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
		return (unlock_mutexes(thread_data->philo), 1);
	}
	thread_data->philo->meal_amount_eaten++;
	if (check_meal_completion(thread_data))
	{
		pthread_mutex_lock(thread_data->philo->meal_time_mutex);
		thread_data->philo->is_eating = 0;
		pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
		return (unlock_mutexes(thread_data->philo), 1);
	}
	unlock_mutexes(thread_data->philo);
	return (0);
}

void	*philosophers_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	if (thread_data->philo->shared_data->philosopher_amount == 1)
		return (handle_single_philosopher(thread_data));
	while (1)
	{
		if (someone_died(thread_data) == 1)
			return (NULL);
		philo_think(thread_data);
		if (process_eating_cycle(thread_data))
			return (NULL);
		if (philo_sleep(thread_data))
		{
			pthread_mutex_lock(thread_data->philo->meal_time_mutex);
			thread_data->philo->is_eating = 0;
			pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
