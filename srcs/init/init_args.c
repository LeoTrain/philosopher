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
