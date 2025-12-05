/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:23 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	allocate_thread_memory(t_program *program,
		t_thread_data **thread_data)
{
	program->threads = malloc(sizeof(pthread_t)
			* program->args.philosopher_amount);
	if (program->threads == NULL)
		return (ERROR_MALLOC);
	*thread_data = malloc(sizeof(t_thread_data)
			* program->args.philosopher_amount);
	if (*thread_data == NULL)
	{
		free(program->threads);
		program->threads = NULL;
		return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

static void	setup_thread_data(t_program *program, t_thread_data *thread_data,
		int index)
{
	thread_data[index].philo = &program->philosophers[index];
	thread_data[index].program = program;
}

static void	cleanup_threads(t_program *program, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(program->threads[i], NULL);
		i++;
	}
}

static void	clean_it(t_program *program, t_thread_data *thread_data, int count)
{
	cleanup_threads(program, count);
	free(program->threads);
	free(thread_data);
	clean_forks(program, program->args.philosopher_amount - 1);
	cleanup_meal_mutexes(program);
}

int	create_and_start_threads(t_program *program)
{
	int				i;
	t_thread_data	*thread_data;

	if (allocate_thread_memory(program, &thread_data) != SUCCESS)
		return (ERROR_MALLOC);
	i = 0;
	while (i < program->args.philosopher_amount)
	{
		setup_thread_data(program, thread_data, i);
		if (pthread_create(&program->threads[i], NULL, &philosophers_routine,
				&thread_data[i]) != 0)
			return (clean_it(program, thread_data, i), ERROR_THREAD);
		i++;
	}
	if (pthread_create(&program->monitor_thread, NULL, &death_monitor,
			program) != 0)
		return (clean_it(program, thread_data, i), ERROR_THREAD);
	program->thread_data = thread_data;
	return (SUCCESS);
}
