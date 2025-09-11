#include "../../includes/philo.h"

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
		if (is_dead(philo))
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
