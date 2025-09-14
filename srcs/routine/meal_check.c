#include "../../includes/philo.h"

static void	set_completion_flag(t_thread_data *thread_data)
{
	pthread_mutex_lock(thread_data->philo->someone_died_mutex);
	thread_data->program->someone_died = 1;
	pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
}

int	check_meal_completion(t_thread_data *thread_data)
{
	if (thread_data->philo->shared_data->max_meals <= 0)
		return (0);
	if (thread_data->philo->meal_amount_eaten
		< thread_data->philo->shared_data->max_meals)
		return (0);
	pthread_mutex_lock(thread_data->philo->completion_counter_mutex);
	*(thread_data->philo->completion_counter) += 1;
	if (*(thread_data->philo->completion_counter)
		>= thread_data->philo->shared_data->philosopher_amount)
		set_completion_flag(thread_data);
	pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
	return (1);
}