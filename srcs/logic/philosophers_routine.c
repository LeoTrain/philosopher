#include "../../includes/philo.h"

static void	lock_mutexes(t_philo *philo);
static void	unlock_mutexes(t_philo *philo);

void	*philosophers_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		philo_think(philo->shared_data->time_to_die);
		lock_mutexes(philo);
		if (philo->meal_time_last >= philo->shared_data->time_to_die)
			return (unlock_mutexes(philo), NULL);
		philo_eat(philo->shared_data->time_to_eat);
		unlock_mutexes(philo);
		philo_sleep(philo->shared_data->time_to_sleep);
	}
	return (NULL);
}

static void	lock_mutexes(t_philo *philo)
{
	if (philo->id < philo->shared_data->philosopher_amount)
	{
		pthread_mutex_lock(philo->fork_left_mutex);
		pthread_mutex_lock(philo->fork_right_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right_mutex);
		pthread_mutex_lock(philo->fork_left_mutex);
	}
}

static void	unlock_mutexes(t_philo *philo)
{
	if (philo->id < philo->shared_data->philosopher_amount)
	{
		pthread_mutex_unlock(philo->fork_left_mutex);
		pthread_mutex_unlock(philo->fork_right_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right_mutex);
		pthread_mutex_unlock(philo->fork_left_mutex);
	}
}
