/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:52:54 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 14:15:57 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	philo_eat(t_thread_data *thread_data)
{
	log_meal(thread_data->philo);
	return (ft_usleep(thread_data->philo->shared_data->time_to_eat,
			thread_data));
}

int	philo_sleep(t_thread_data *thread_data)
{
	log_sleep(thread_data->philo);
	return (ft_usleep(thread_data->philo->shared_data->time_to_sleep,
			thread_data));
}

int	philo_think(t_thread_data *thread_data)
{
	long	think_time;

	log_think(thread_data->philo);
	think_time = thread_data->philo->shared_data->time_to_eat
		- thread_data->philo->shared_data->time_to_sleep;
	if (think_time > 0)
		return (ft_usleep(think_time, thread_data));
	return (0);
}
