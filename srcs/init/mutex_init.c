#include "../../includes/philo.h"

static int	init_fork_mutexes(t_program *program)
{
	int	i;

	program->forks_mutex = malloc(sizeof(pthread_mutex_t)
			* program->args.philosopher_amount);
	if (program->forks_mutex == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		if (pthread_mutex_init(&program->forks_mutex[i], NULL) != 0)
			return (clean_forks(program, i - 1), ERROR_MUTEX);
		i++;
	}
	return (SUCCESS);
}

static int	init_meal_time_mutexes(t_program *program)
{
	int	i;

	program->meal_time_mutexes = malloc(sizeof(pthread_mutex_t)
						* program->args.philosopher_amount);
	if (program->meal_time_mutexes == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		if (pthread_mutex_init(&program->meal_time_mutexes[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&program->meal_time_mutexes[i]);
			free(program->meal_time_mutexes);
			return (ERROR_MUTEX);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_control_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->completion_counter_mutex, NULL) != 0)
		return (clean_forks(program, program->args.philosopher_amount),
			ERROR_MUTEX);
	if (pthread_mutex_init(&program->logging_mutex, NULL) != 0)
		return (clean_forks(program, program->args.philosopher_amount),
			pthread_mutex_destroy(&program->completion_counter_mutex),
			ERROR_MUTEX);
	if (pthread_mutex_init(&program->someone_died_mutex, NULL) != 0)
		return (clean_forks(program, program->args.philosopher_amount),
			pthread_mutex_destroy(&program->completion_counter_mutex),
			pthread_mutex_destroy(&program->logging_mutex),
			ERROR_MUTEX);
	return (SUCCESS);
}

int	init_mutexes(t_program *program)
{
	if (init_fork_mutexes(program) != SUCCESS)
		return (ERROR_MUTEX);
	if (init_meal_time_mutexes(program) != SUCCESS)
	{
		clean_forks(program, program->args.philosopher_amount - 1);
		return (ERROR_MUTEX);
	}
	if (init_control_mutexes(program) != SUCCESS)
	{
		clean_forks(program, program->args.philosopher_amount - 1);
		cleanup_meal_mutexes(program);
		return (ERROR_MUTEX);
	}
	return (SUCCESS);
}
