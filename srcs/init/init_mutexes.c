#include "../../includes/philo.h"

int	init_mutexes(t_program *program)
{
	int	i;

	program->forks_mutex = malloc(sizeof(pthread_mutex_t) * program->args.philosopher_amount);
	if (program->forks_mutex == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		if (pthread_mutex_init(&program->forks_mutex[i], NULL) != 0)
			return (clean_forks(program, i - 1), ERROR_MUTEX);
		i++;
	}
	if (pthread_mutex_init(&program->completion_counter_mutex, NULL) != 0)
			return (clean_forks(program, program->args.philosopher_amount), ERROR_MUTEX);
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

