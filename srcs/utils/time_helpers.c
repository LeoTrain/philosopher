#include "../../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_elapsed_time(long start_time)
{
	return (get_current_time() - start_time);
}

static int	is_simulation_over(t_thread_data *thread_data)
{
	int	died;
	int	full;

	pthread_mutex_lock(thread_data->philo->someone_died_mutex);
	died = thread_data->program->someone_died;
	pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
	pthread_mutex_lock(thread_data->philo->completion_counter_mutex);
	full = thread_data->program->completion_counter_full;
	pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
	return (died || full);
}

int	ft_usleep(long duration_ms, t_thread_data *thread_data)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < duration_ms)
	{
		if (is_simulation_over(thread_data))
			return (1);
		usleep(100);
	}
	return (0);
}
