/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:20 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static t_error_code	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_pair.left_fork);
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_unlock(philo->fork_pair.left_fork);
	return (ERROR_NONE);
}

static t_error_code	take_even_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_pair.right_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->fork_pair.right_fork);
		return (ERROR_NONE);
	}
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_pair.left_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->fork_pair.left_fork);
		pthread_mutex_unlock(philo->fork_pair.right_fork);
		return (ERROR_NONE);
	}
	print_philo_action(philo, "has taken a fork");
	return (ERROR_NONE);
}

static t_error_code	take_odd_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_pair.left_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->fork_pair.left_fork);
		return (ERROR_NONE);
	}
	print_philo_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_pair.right_fork);
	if (is_simulation_over(philo->config))
	{
		pthread_mutex_unlock(philo->fork_pair.right_fork);
		pthread_mutex_unlock(philo->fork_pair.left_fork);
		return (ERROR_NONE);
	}
	print_philo_action(philo, "has taken a fork");
	return (ERROR_NONE);
}

t_error_code	take_forks(t_philo *philo)
{
	if (philo->config->philo_count == 1)
		return (handle_single_philo(philo));
	if (philo->id % 2 == 0)
		return (take_even_forks(philo));
	else
		return (take_odd_forks(philo));
}

t_error_code	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_pair.left_fork);
	pthread_mutex_unlock(philo->fork_pair.right_fork);
	return (ERROR_NONE);
}
