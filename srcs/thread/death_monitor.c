#include "../../includes/philo.h"

static int	check_philosopher_death(t_philo *philo, t_program *program)
{
	long	current_time;
	long	last_meal;
	int		eating;

	pthread_mutex_lock(&program->completion_counter_mutex);
	if (program->completion_counter_full == 1)
	{
		pthread_mutex_unlock(&program->completion_counter_mutex);
		return (1);
	}
	pthread_mutex_unlock(&program->completion_counter_mutex);

	pthread_mutex_lock(philo->meal_time_mutex);
	last_meal = philo->meal_time_last;
	eating = philo->is_eating;
	pthread_mutex_unlock(philo->meal_time_mutex);
	if (eating)
		return (0);
	current_time = get_current_time();
	if (current_time - last_meal > philo->shared_data->time_to_die)
	{
		pthread_mutex_lock(philo->someone_died_mutex);
		if (program->someone_died == 0)
		{
			program->someone_died = 1;
			pthread_mutex_unlock(philo->someone_died_mutex);
			log_dead(philo);
			return (1);
		}
		pthread_mutex_unlock(philo->someone_died_mutex);
		return (1);
	}
	return (0);
}

static int	check_meal_completion_monitor(t_program *program)
{
	int	completed;

	if (program->args.max_meals <= 0)
		return (0);
	pthread_mutex_lock(&program->completion_counter_mutex);
	completed = program->completion_counter;
	pthread_mutex_unlock(&program->completion_counter_mutex);
	if (completed >= program->args.philosopher_amount)
	{
		pthread_mutex_lock(&program->someone_died_mutex);
		program->someone_died = 1;
		pthread_mutex_unlock(&program->someone_died_mutex);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	int			i;
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		i = 0;
		while (i < program->args.philosopher_amount)
		{
			if (check_philosopher_death(&program->philosophers[i], program))
				return (NULL);
			i++;
		}
		if (check_meal_completion_monitor(program))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
