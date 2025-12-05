#include "../../includes/philo.h"

int	check_meal_completion(t_thread_data *thread_data)
{
	int	meals_eaten;
	int	counter;

	if (thread_data->program->completion_counter_full)
		return (1);
	if (thread_data->philo->shared_data->max_meals == -1)
		return (0);
	pthread_mutex_lock(thread_data->philo->meal_time_mutex);
	meals_eaten = thread_data->philo->meal_amount_eaten;
	pthread_mutex_unlock(thread_data->philo->meal_time_mutex);
	if (meals_eaten < thread_data->philo->shared_data->max_meals)
		return (0);
	pthread_mutex_lock(thread_data->philo->completion_counter_mutex);
	if (thread_data->program->completion_counter_full)
	{
		pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
		return (1);
	}
	*(thread_data->philo->completion_counter) += 1;
	counter = *(thread_data->philo->completion_counter);
	if (counter >= thread_data->philo->shared_data->philosopher_amount)
		thread_data->program->completion_counter_full = 1;
	pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
	return (1);
}
