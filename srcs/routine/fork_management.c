/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:13 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:26 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	determine_fork_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->fork_left_mutex;
		*second_fork = philo->fork_right_mutex;
	}
	else
	{
		*second_fork = philo->fork_left_mutex;
		*first_fork = philo->fork_right_mutex;
	}
}

void	lock_mutexes(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
		usleep(500);
	determine_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	log_fork(philo);
	pthread_mutex_lock(second_fork);
	log_fork(philo);
}
