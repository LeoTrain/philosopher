#include "../../includes/philo.h"

static int	process_eating_cycle(t_thread_data *thread_data)
{
	if (someone_died(thread_data) == 1)
		return (1);
	lock_mutexes(thread_data->philo);
	if (is_dead(thread_data) == 1)
		return (unlock_mutexes(thread_data->philo), 1);
	if (someone_died(thread_data) == 1)
		return (unlock_mutexes(thread_data->philo), 1);
	philo_eat(thread_data->philo);
	thread_data->philo->meal_time_last = get_current_time();
	thread_data->philo->meal_amount_eaten++;
	if (someone_died(thread_data) == 1)
		return (unlock_mutexes(thread_data->philo), 1);
	if (check_meal_completion(thread_data))
		return (unlock_mutexes(thread_data->philo), 1);
	unlock_mutexes(thread_data->philo);
	return (0);
}

void	*philosophers_routine(void *arg)
{
	t_thread_data	*thread_data;

	thread_data = (t_thread_data *)arg;
	if (thread_data->philo->shared_data->philosopher_amount == 1)
		return (handle_single_philosopher(thread_data));
	while (1)
	{
		if (someone_died(thread_data) == 1)
			return (NULL);
		philo_think(thread_data->philo);
		if (process_eating_cycle(thread_data))
			return (NULL);
		if (someone_died(thread_data) == 1)
			return (NULL);
		philo_sleep(thread_data->philo);
	}
	return (NULL);
}