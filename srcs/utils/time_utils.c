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

int	is_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time();
	if (current_time - philo->meal_time_last > philo->shared_data->time_to_die)
	{
		log_dead(philo);
		return (1);
	}
	return (0);
}
