#include "../../includes/philo.h"

static int	is_simulation_over(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(philo->someone_died_mutex);
	died = *philo->someone_died;
	pthread_mutex_unlock(philo->someone_died_mutex);
	return (died);
}

void	log_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	if (!is_simulation_over(philo))
		printf("%ld %d has taken a fork\n",
			get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}

void	log_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	if (!is_simulation_over(philo))
		printf("%ld %d is eating\n",
			get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}

void	log_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	if (!is_simulation_over(philo))
		printf("%ld %d is sleeping\n",
			get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}
