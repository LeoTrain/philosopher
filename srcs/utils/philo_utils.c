#include "../../includes/philo.h"

void	add_start_time_to_args(t_program *program)
{
	program->args.start_time = get_current_time();
}

int	create_and_start_threads(t_program *program)
{
	int				i;
	t_thread_data	*thread_data;

	program->threads = malloc(sizeof(pthread_t) * program->args.philosopher_amount);
	if (program->threads == NULL)
		return (ERROR_MALLOC);
	thread_data = malloc(sizeof(t_thread_data) * program->args.philosopher_amount);
	if (thread_data == NULL)
		return (free(program->threads), ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		thread_data[i].philo = &program->philosophers[i];
		thread_data[i].program = program;
		if (pthread_create(&program->threads[i], NULL, &philosophers_routine, &thread_data[i]) != 0)
		{
			free(thread_data);
			clean_forks(program, i);
			return (ERROR_THREAD);
		}
		i++;
	}
	program->thread_data = thread_data;
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
	free(program->thread_data);
	program->thread_data = NULL;
}
