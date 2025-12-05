#include "../../includes/philo.h"

static void	determine_unlock_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->fork_left_mutex;
		*second_fork = philo->fork_right_mutex;
	}
	else
	{
		*second_fork = philo->fork_left_mutex;
		*first_fork = philo->fork_right_mutex;
	}
}

void	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	determine_unlock_order(philo, &first_fork, &second_fork);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
