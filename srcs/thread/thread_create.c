#include "../../includes/philo.h"

static int	allocate_thread_memory(t_program *program,
		t_thread_data **thread_data)
{
	program->threads = malloc(sizeof(pthread_t)
			* program->args.philosopher_amount);
	if (program->threads == NULL)
		return (ERROR_MALLOC);
	*thread_data = malloc(sizeof(t_thread_data)
			* program->args.philosopher_amount);
	if (*thread_data == NULL)
		return (free(program->threads), ERROR_MALLOC);
	return (SUCCESS);
}

static void	setup_thread_data(t_program *program, t_thread_data *thread_data,
		int index)
{
	thread_data[index].philo = &program->philosophers[index];
	thread_data[index].program = program;
}

int	create_and_start_threads(t_program *program)
{
	int				i;
	t_thread_data	*thread_data;

	if (allocate_thread_memory(program, &thread_data) != SUCCESS)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		setup_thread_data(program, thread_data, i);
		if (pthread_create(&program->threads[i], NULL, &philosophers_routine,
				&thread_data[i]) != 0)
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