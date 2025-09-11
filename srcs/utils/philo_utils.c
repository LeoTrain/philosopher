#include "../../includes/philo.h"

void	add_start_time_to_args(t_program *program)
{
	program->args.start_time = get_current_time();
}

int	create_and_start_threads(t_program *program)
{
	int	i;

	program->threads = malloc(sizeof(pthread_t) * program->args.philosopher_amount);
	if (program->threads == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		if (pthread_create(&program->threads[i], NULL, &philosophers_routine, &program->philosophers[i]) != 0)
		{
			clean_forks(program, i);
			return (ERROR_THREAD);
		}
		i++;
	}
	return (SUCCESS);
}

void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args.philosopher_amount)
	{
		pthread_join(program->threads[i], NULL);
		i++;
	}
	free(program->threads);
	program->threads = NULL;
}
