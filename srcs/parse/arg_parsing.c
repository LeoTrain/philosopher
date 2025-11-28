#include "../../includes/philo.h"

static int	parse_required_args(char **argv, t_program *program)
{
	if (!is_number(argv[1]) || !is_number(argv[2])
		|| !is_number(argv[3]) || !is_number(argv[4]))
		return (FAILURE);
	program->args.philosopher_amount = ft_atoi(argv[1]);
	program->args.time_to_die = ft_atol(argv[2]);
	program->args.time_to_eat = ft_atol(argv[3]);
	program->args.time_to_sleep = ft_atol(argv[4]);
	return (SUCCESS);
}

static int	parse_optional_arg(char **argv, t_program *program, int argc)
{
	if (argc == 6)
	{
		if (!is_number(argv[5]))
			return (FAILURE);
		program->args.max_meals = ft_atoi(argv[5]);
	}
	else
		program->args.max_meals = 0;
	return (SUCCESS);
}

int	parse_arguments(int argc, char **argv, t_program *program)
{
	if (argc < 5 || argc > 6)
		return (FAILURE);
	if (initialize_program_args(&program->args) != SUCCESS)
		return (FAILURE);
	if (parse_required_args(argv, program) != SUCCESS)
		return (FAILURE);
	if (parse_optional_arg(argv, program, argc) != SUCCESS)
		return (FAILURE);
	if (check_args(program->args) != SUCCESS)
		return (FAILURE);
	program->someone_died = 0;
	return (SUCCESS);
}
