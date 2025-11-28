#include "../../includes/philo.h"

static int	is_simulation_over(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(philo->someone_died_mutex);
	died = *philo->someone_died;
	pthread_mutex_unlock(philo->someone_died_mutex);
	return (died);
}

void	log_think(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	if (!is_simulation_over(philo))
		printf("%ld %d is thinking\n",
			get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}

void	log_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	printf("%ld %d died\n",
		get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}
