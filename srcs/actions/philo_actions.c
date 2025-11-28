#include "../../includes/philo.h"

int	philo_eat(t_thread_data *thread_data)
{
	log_meal(thread_data->philo);
	return (ft_usleep(thread_data->philo->shared_data->time_to_eat,
			thread_data));
}

int	philo_sleep(t_thread_data *thread_data)
{
	log_sleep(thread_data->philo);
	return (ft_usleep(thread_data->philo->shared_data->time_to_sleep,
			thread_data));
}

void	philo_think(t_thread_data *thread_data)
{
	log_think(thread_data->philo);
}
