/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:08 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	log_think(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	if (!is_philo_sim_over(philo))
		printf("%ld %d is thinking\n",
			get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}

void	log_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->logging_mutex);
	printf("%ld %d died\n",
		get_elapsed_time(philo->shared_data->start_time), philo->id);
	pthread_mutex_unlock(philo->logging_mutex);
}
