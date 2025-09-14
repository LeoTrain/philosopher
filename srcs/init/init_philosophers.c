#include "../../includes/philo.h"
#include <stdio.h>

int	create_philosophers(t_program *program)
{
	int	i;
	int	left_fork_id;

	program->philosophers = malloc(sizeof(t_philo) * program->args.philosopher_amount);
	if (program->philosophers == NULL)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		program->philosophers[i].id = i + 1;
		program->philosophers[i].meal_time_last = program->args.start_time;
		program->philosophers[i].meal_amount_eaten = 0;
		left_fork_id = (i + program->args.philosopher_amount - 1) % program->args.philosopher_amount;
		program->philosophers[i].fork_left_mutex = &program->forks_mutex[left_fork_id];
		program->philosophers[i].fork_right_mutex = &program->forks_mutex[i];
		program->philosophers[i].completion_counter_mutex = &program->completion_counter_mutex;
		program->philosophers[i].completion_counter = &program->completion_counter;
		program->philosophers[i].shared_data = &program->args;
		program->philosophers[i].logging_mutex = &program->logging_mutex;
		program->philosophers[i].someone_died_mutex = &program->someone_died_mutex;
		i++;
	}
	return (SUCCESS);
}
