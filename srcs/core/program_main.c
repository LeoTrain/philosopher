#include "../../includes/philo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	program.completion_counter = 0;
	program.someone_died = 0;
	if (parse_arguments(argc, argv, &program) != SUCCESS)
	{
		printf("Error: parsing the arguments\n");
		return (EXIT_FAILURE);
	}
	if (init_mutexes(&program) != SUCCESS)
	{
		printf("Error: inititializing mutexes");
		return (EXIT_FAILURE);
	}
	add_start_time_to_args(&program);
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
	cleanup_meal_mutexes(&program);
	pthread_mutex_destroy(&program.completion_counter_mutex);
	pthread_mutex_destroy(&program.logging_mutex);
	pthread_mutex_destroy(&program.someone_died_mutex);
	free(program.forks_mutex);
	free(program.philosophers);
	return (EXIT_SUCCESS);
}
