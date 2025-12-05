/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:53:28 by leberton          #+#    #+#             */
/*   Updated: 2025/12/05 13:53:35 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	someone_died(t_thread_data *thread_data)
{
	int	died;

	pthread_mutex_lock(thread_data->philo->someone_died_mutex);
	died = thread_data->program->someone_died;
	pthread_mutex_unlock(thread_data->philo->someone_died_mutex);
	return (died);
}
