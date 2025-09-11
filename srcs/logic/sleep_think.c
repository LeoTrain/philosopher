#include "../../includes/philo.h"

void	philo_sleep(t_philo *philo)
{
	log_sleep(philo);
	usleep(philo->shared_data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	log_think(philo);
	usleep(philo->shared_data->time_to_die / 10 * 1000);
}
