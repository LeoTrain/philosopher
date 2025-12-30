/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:51 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_error_code	init_and_validate(int argc, char **argv,
	t_simulation *sim)
{
	t_error_code	error;

	error = validate_all_args(argc, argv);
	if (error != ERROR_NONE)
		return (printf("Invalid argument detected\n"), error);
	error = init_simulation_config(argc, argv, &sim->config);
	if (error != ERROR_NONE)
		return (printf("Error initializing config\n"), error);
	return (ERROR_NONE);
}

static t_error_code	init_resources(t_simulation *sim)
{
	t_error_code	error;

	error = init_fork_mutexes(sim);
	if (error != ERROR_NONE)
		return (printf("Error initializing forks\n"), error);
	error = init_philosophers(sim);
	if (error != ERROR_NONE)
		return (cleanup_simulation(sim, 2),
			printf("Error initializing philosophers\n"), error);
	return (ERROR_NONE);
}

static t_error_code	start_simulation(t_simulation *sim)
{
	t_error_code	error;

	error = create_philo_threads(sim);
	if (error != ERROR_NONE)
		return (cleanup_simulation(sim, 3),
			printf("Error creating threads\n"), error);
	error = create_death_monitor(sim);
	if (error != ERROR_NONE)
		return (stop_simulation(&sim->config), cleanup_simulation(sim, 4),
			printf("Error creating monitor\n"), error);
	return (ERROR_NONE);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_error_code	error;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (ERROR_ARGC);
	}
	error = init_and_validate(argc, argv, &sim);
	if (error != ERROR_NONE)
		return (error);
	error = init_resources(&sim);
	if (error != ERROR_NONE)
		return (error);
	error = start_simulation(&sim);
	if (error != ERROR_NONE)
		return (error);
	error = join_all_threads(&sim);
	if (error != ERROR_NONE)
		return (cleanup_simulation(&sim, 4),
			printf("Error joining threads\n"), error);
	cleanup_simulation(&sim, 4);
	return (EXIT_SUCCESS);
}
