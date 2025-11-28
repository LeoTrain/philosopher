#include "../../includes/philo.h"

static void	determine_unlock_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = (philo->id - 1 + philo->shared_data->philosopher_amount - 1)
		% philo->shared_data->philosopher_amount;
	right_fork_id = philo->id - 1;
	if (left_fork_id < right_fork_id)
	{
		*first_fork = philo->fork_left_mutex;
		*second_fork = philo->fork_right_mutex;
	}
	else
	{
		*first_fork = philo->fork_right_mutex;
		*second_fork = philo->fork_left_mutex;
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
