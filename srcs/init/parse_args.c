#include "../../includes/philo.h"

static int	check_args(t_program_args args);

int	parse_arguments(int argc, char **argv, t_program *program)
{
	if (argc != 5 && argc != 6)
		return (ERROR_ARGS);
	initialize_program_args(&program->args);
	if (is_number(argv[1]) == SUCCESS)
		program->args.philosopher_amount = ft_atoi(argv[1]);
	else
		return (ERROR_ARGS);
	if (is_number(argv[2]) == SUCCESS)
		program->args.time_to_die = ft_atol(argv[2]);
	else
		return (ERROR_ARGS);
	if (is_number(argv[3]) == SUCCESS)
		program->args.time_to_eat = ft_atol(argv[3]);
	else
		return (ERROR_ARGS);
	if (is_number(argv[4]) == SUCCESS)
		program->args.time_to_sleep = ft_atol(argv[4]);
	else
		return (ERROR_ARGS);
	if (argc == 6)
	{
		if (is_number(argv[5]) == SUCCESS)
			program->args.max_meals = ft_atol(argv[5]);
		else
			return (ERROR_ARGS);
	}
	else
		program->args.max_meals = -1;
	return (check_args(program->args));
}

static int	check_args(t_program_args args)
{
	if (args.philosopher_amount < 1)
		return (ERROR_ARGS);
	if (args.time_to_die <= 0 || args.time_to_eat <= 0
		|| args.time_to_sleep <= 0 || args.max_meals < -1)
		return (ERROR_ARGS);
	return (SUCCESS);
}
