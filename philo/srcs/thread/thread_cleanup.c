/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:22 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	add_start_time_to_args(t_program *program)
{
	program->args.start_time = get_current_time()
		+ (program->args.philosopher_amount * 2);
}

void	join_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->args.philosopher_amount)
	{
		pthread_join(program->threads[i], NULL);
		i++;
	}
	pthread_join(program->monitor_thread, NULL);
	free(program->threads);
	program->threads = NULL;
	free(program->thread_data);
	program->thread_data = NULL;
}
