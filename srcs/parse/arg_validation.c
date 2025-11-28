#include "../../includes/philo.h"

static int	validate_philosopher_count(int philosopher_amount)
{
	if (philosopher_amount <= 0 || philosopher_amount > 200)
		return (FAILURE);
	return (SUCCESS);
}

static int	validate_timing_args(t_program_args args)
{
	if (args.time_to_die <= 0)
		return (FAILURE);
	if (args.time_to_eat <= 0)
		return (FAILURE);
	if (args.time_to_sleep <= 0)
		return (FAILURE);
	return (SUCCESS);
}

int	check_args(t_program_args args)
{
	if (validate_philosopher_count(args.philosopher_amount) != SUCCESS)
		return (FAILURE);
	if (validate_timing_args(args) != SUCCESS)
		return (FAILURE);
	if (args.max_meals < 0)
		return (FAILURE);
	return (SUCCESS);
}
