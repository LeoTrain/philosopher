#include "../../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	log_meal(philo);
	usleep(philo->shared_data->time_to_eat * 1000);
}
