/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:52:58 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	parse_and_init(int argc, char **argv, t_program *program)
{
	program->completion_counter = 0;
	program->completion_counter_full = 0;
	program->someone_died = 0;
	if (parse_arguments(argc, argv, program) != SUCCESS)
	{
		printf("Error: parsing the arguments\n");
		return (EXIT_FAILURE);
	}
	if (init_mutexes(program) != SUCCESS)
	{
		printf("Error: inititializing mutexes\n");
		return (EXIT_FAILURE);
	}
	add_start_time_to_args(program);
	return (SUCCESS);
}

static void	cleanup_resources(t_program *program)
{
	cleanup_meal_mutexes(program);
	pthread_mutex_destroy(&program->completion_counter_mutex);
	pthread_mutex_destroy(&program->logging_mutex);
	pthread_mutex_destroy(&program->someone_died_mutex);
	clean_forks(program, program->args.philosopher_amount - 1);
}

static void	main_cleanup(t_program *program, int philo_created)
{
	if (philo_created)
		free(program->philosophers);
	cleanup_resources(program);
}

static void	main_final(t_program *program)
{
	join_threads(program);
	cleanup_resources(program);
	free(program->philosophers);
}

int	main(int argc, char **argv)
{
	t_program	program;

	program.forks_mutex = NULL;
	program.meal_time_mutexes = NULL;
	program.philosophers = NULL;
	program.threads = NULL;
	program.thread_data = NULL;
	if (parse_and_init(argc, argv, &program) != SUCCESS)
		return (EXIT_FAILURE);
	if (create_philosophers(&program) != SUCCESS)
	{
		printf("Error: creating philosophers\n");
		main_cleanup(&program, 0);
		return (EXIT_FAILURE);
	}
	if (create_and_start_threads(&program) != SUCCESS)
	{
		printf("Error: creating and starting threads\n");
		main_cleanup(&program, 1);
		return (EXIT_FAILURE);
	}
	main_final(&program);
	return (EXIT_SUCCESS);
}
