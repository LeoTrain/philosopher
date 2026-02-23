/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:18 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <pthread.h>

void	*handle_single_philosopher(t_thread_data *thread_data)
{
	while (get_current_time() < thread_data->philo->shared_data->start_time)
		usleep(50);
	pthread_mutex_lock(thread_data->philo->fork_left_mutex);
	log_fork(thread_data->philo);
	while (!someone_died(thread_data))
		usleep(100);
	pthread_mutex_unlock(thread_data->philo->fork_left_mutex);
	return (NULL);
}
