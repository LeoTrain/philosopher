#include "../../includes/philo.h"
#include <bits/pthreadtypes.h>

static void	lock_mutexes(t_philo *philo);
static void	unlock_mutexes(t_philo *philo);

void	*philosophers_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		philo_think(philo);
		lock_mutexes(philo);
		if (is_dead(philo) || someone_died(philo))
			return (unlock_mutexes(philo), NULL);
		philo_eat(philo);
		philo->meal_time_last = get_current_time();
		philo->meal_amount_eaten++;
		if (philo->shared_data->max_meals > 0 && philo->meal_amount_eaten >= philo->shared_data->max_meals)
		{
			pthread_mutex_lock(philo->completion_counter_mutex);
			*(philo->completion_counter) += 1;
			pthread_mutex_unlock(philo->completion_counter_mutex);
			return (unlock_mutexes(philo), NULL);
		}
		unlock_mutexes(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

static void	lock_mutexes(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	int				left_fork_id;
	int				right_fork_id;

	left_fork_id = (philo->id - 1 + philo->shared_data->philosopher_amount - 1)\
					% philo->shared_data->philosopher_amount;
	right_fork_id = philo->id - 1;
	if (left_fork_id < right_fork_id)
	{
		first_fork = philo->fork_left_mutex;
		second_fork = philo->fork_right_mutex;
	}
	else
	{
		first_fork = philo->fork_right_mutex;
		second_fork = philo->fork_left_mutex;	
	}
	pthread_mutex_lock(first_fork);
	log_fork(philo);
	pthread_mutex_lock(second_fork);
	log_fork(philo);
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
