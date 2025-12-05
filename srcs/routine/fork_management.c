#include "../../includes/philo.h"

static void	determine_fork_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	// int	left_fork_id;
	// int	right_fork_id;

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
	// left_fork_id = (philo->id - 1 + philo->shared_data->philosopher_amount - 1)
	// 	% philo->shared_data->philosopher_amount;
	// right_fork_id = philo->id - 1;
	// if (left_fork_id < right_fork_id)
	// {
	// 	*first_fork = philo->fork_left_mutex;
	// 	*second_fork = philo->fork_right_mutex;
	// }
	// else
	// {
	// 	*first_fork = philo->fork_right_mutex;
	// 	*second_fork = philo->fork_left_mutex;
	// }
}

void	lock_mutexes(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
		usleep(500);
	determine_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	log_fork(philo);
	pthread_mutex_lock(second_fork);
	log_fork(philo);
}
