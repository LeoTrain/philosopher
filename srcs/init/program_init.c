#include "../../includes/philo.h"

int	initialize_program_args(t_program_args *args)
{
	args->philosopher_amount = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->max_meals = 0;
	args->start_time = 0;
	return (SUCCESS);
}

void	clean_forks(t_program *program, int i)
{
	if (program->forks_mutex == NULL)
		return ;
	while (i >= 0)
	{
		pthread_mutex_destroy(&program->forks_mutex[i]);
		i--;
	}
	free(program->forks_mutex);
	program->forks_mutex = NULL;
}

void	cleanup_meal_mutexes(t_program *program)
{
	int	i;

	if (program->meal_time_mutexes == NULL)
		return ;
	i = program->args.philosopher_amount - 1;
	while (i >= 0)
	{
		pthread_mutex_destroy(&program->meal_time_mutexes[i]);
		i--;
	}
	free(program->meal_time_mutexes);
	program->meal_time_mutexes = NULL;
}
