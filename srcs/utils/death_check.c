#include "../../includes/philo.h"

int	is_dead(t_thread_data *thread_data)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time - thread_data->philo->meal_time_last
		> thread_data->philo->shared_data->time_to_die)
	{
		pthread_mutex_lock(thread_data->philo->someone_died_mutex);
		if (thread_data->program->someone_died == 1)
		{
			pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
			return (1);
		}
		thread_data->program->someone_died = 1;
		pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
		log_dead(thread_data->philo);
		return (1);
	}
	return (0);
}

int	someone_died(t_thread_data *thread_data)
{
	int	died;

	pthread_mutex_lock(thread_data->philo->someone_died_mutex);
	died = thread_data->program->someone_died;
	pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
	return (died);
}
