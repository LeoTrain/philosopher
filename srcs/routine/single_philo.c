#include "../../includes/philo.h"

static void	handle_single_death(t_thread_data *thread_data)
{
	pthread_mutex_lock(thread_data->philo->someone_died_mutex);
	thread_data->program->someone_died = 1;
	pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
	log_dead(thread_data->philo);
}

void	*handle_single_philosopher(t_thread_data *thread_data)
{
	philo_think(thread_data->philo);
	usleep(thread_data->philo->shared_data->time_to_die * 1000 + 1000);
	handle_single_death(thread_data);
	return (NULL);
}