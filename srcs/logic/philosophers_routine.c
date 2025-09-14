#include "../../includes/philo.h"

static void	lock_mutexes(t_philo *philo);
static void	unlock_mutexes(t_philo *philo);

void	*philosophers_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	if (thread_data->philo->shared_data->philosopher_amount == 1)
	{
		philo_think(thread_data->philo);
		usleep(thread_data->philo->shared_data->time_to_die * 1000 + 1000);
		pthread_mutex_lock(thread_data->philo->someone_died_mutex);
		thread_data->program->someone_died = 1;
		pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
		log_dead(thread_data->philo);
		return (NULL);
	}
	while (1)
	{
		if (someone_died(thread_data) == 1)
			return (NULL);
		philo_think(thread_data->philo);
		if (someone_died(thread_data) == 1)
			return (NULL);
		lock_mutexes(thread_data->philo);
		if (is_dead(thread_data) == 1)
			return (unlock_mutexes(thread_data->philo), NULL);
		if (someone_died(thread_data) == 1)
			return (unlock_mutexes(thread_data->philo), NULL);
		philo_eat(thread_data->philo);
		thread_data->philo->meal_time_last = get_current_time();
		thread_data->philo->meal_amount_eaten++;
		if (someone_died(thread_data) == 1)
			return (unlock_mutexes(thread_data->philo), NULL);
		if (thread_data->philo->shared_data->max_meals > 0 && thread_data->philo->meal_amount_eaten >= thread_data->philo->shared_data->max_meals)
		{
			pthread_mutex_lock(thread_data->philo->completion_counter_mutex);
			*(thread_data->philo->completion_counter) += 1;
			if (*(thread_data->philo->completion_counter) >= thread_data->philo->shared_data->philosopher_amount)
			{
				pthread_mutex_lock(thread_data->philo->someone_died_mutex);
				thread_data->program->someone_died = 1;
				pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
			}
			pthread_mutex_unlock(thread_data->philo->completion_counter_mutex);
			return (unlock_mutexes(thread_data->philo), NULL);
		}
		unlock_mutexes(thread_data->philo);
		if (someone_died(thread_data) == 1)
			return (NULL);
		philo_sleep(thread_data->philo);
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
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
