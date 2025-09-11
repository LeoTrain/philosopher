#include "../../includes/philo.h"

static void	print_arguments(t_program_args args)
{
	printf("===== ARGUMENTS =====\n");
	printf("Philo's amount: %d\n", args.philosopher_amount);
	printf("Time to die:    %ld\n", args.time_to_die);
	printf("Time to eat:    %ld\n", args.time_to_eat);
	printf("Time to sleep:  %ld\n", args.time_to_sleep);
	printf("Max meals:      %d\n", args.max_meals);
}

int	main(int argc, char **argv)
{
	t_program	program;

	program.completion_counter = 0;
	if (parse_arguments(argc, argv, &program) != SUCCESS)
	{
		printf("Error: parsing the arguments\n");
		return (EXIT_FAILURE);
	}
	(void)print_arguments;
	if (init_mutexes(&program) != SUCCESS)
	{
		printf("Error: inititializing mutexes");
		return (EXIT_FAILURE);
	}
	add_start_time_to_args(&program);
	printf("Start time: %ld\n", program.args.start_time);
	if (create_philosophers(&program) != SUCCESS)
	{
		printf("Error: creating philosophers\n");
		return (EXIT_FAILURE);
	}
	if (create_and_start_threads(&program) != SUCCESS)
	{
		printf("Error: creating and starting threads\n");
		return (EXIT_FAILURE);
	}
	join_threads(&program);
	clean_forks(&program, program.args.philosopher_amount);
	free(program.philosophers);
	return (EXIT_SUCCESS);
}
