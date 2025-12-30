/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:03 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	is_simulation_over(t_simulation_config *config)
{
	int	is_over;

	pthread_mutex_lock(&config->sim_state_lock);
	is_over = !config->is_simulation_running;
	pthread_mutex_unlock(&config->sim_state_lock);
	return (is_over);
}

void	stop_simulation(t_simulation_config *config)
{
	pthread_mutex_lock(&config->sim_state_lock);
	config->is_simulation_running = 0;
	pthread_mutex_unlock(&config->sim_state_lock);
}

t_error_code	print_philo_action(t_philo *philo, const char *action)
{
	long	current_time;

	if (is_simulation_over(philo->config))
		return (ERROR_NONE);
	current_time = get_time_ms() - philo->config->sim_start_time_ms;
	pthread_mutex_lock(&philo->config->print_lock);
	if (philo->config->is_simulation_running)
		printf("%ld %d %s\n", current_time, philo->id, action);
	pthread_mutex_unlock(&philo->config->print_lock);
	return (ERROR_NONE);
}
