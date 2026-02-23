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

int	is_delayed_philo(t_philo *philo)
{
	int	id;
	int	total;

	id = philo->id;
	total = philo->shared_data->philosopher_amount;
	if (id % 2 == 0)
		return (1);
	if (total % 2 == 1 && id == total)
		return (1);
	return (0);
}

static void	determine_fork_order(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (!is_delayed_philo(philo))
	{
		*first_fork = philo->fork_left_mutex;
		*second_fork = philo->fork_right_mutex;
	}
	else
	{
		*first_fork = philo->fork_right_mutex;
		*second_fork = philo->fork_left_mutex;
	}
}

void	lock_mutexes(t_thread_data *thread_data)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_philo			*philo;

	philo = thread_data->philo;
	determine_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (someone_died(thread_data) == 1)
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	log_fork(philo);
	pthread_mutex_lock(second_fork);
	if (someone_died(thread_data) == 1)
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	log_fork(philo);
}

void	unlock_mutexes(t_thread_data *thread_data)
{
	pthread_mutex_unlock(thread_data->philo->fork_left_mutex);
	pthread_mutex_unlock(thread_data->philo->fork_right_mutex);
}
