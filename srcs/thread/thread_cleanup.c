#include "../../includes/philo.h"

void	add_start_time_to_args(t_program *program)
{
	program->args.start_time = get_current_time();
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
