/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:56 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	should_continue(t_philo *philo, int local_meals)
{
	if (is_simulation_over(philo->config))
		return (0);
	if (philo->config->required_meal_count != -1
		&& local_meals >= philo->config->required_meal_count)
		return (0);
	return (1);
}

static int	get_meal_count(t_philo *philo)
{
	int	local_meals;

	pthread_mutex_lock(&philo->meal_lock);
	local_meals = philo->meal_count;
	pthread_mutex_unlock(&philo->meal_lock);
	return (local_meals);
}

void	*philo_lifecycle(void *arg)
{
	t_philo	*philo;
	int		local_meals;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		local_meals = get_meal_count(philo);
		if (!should_continue(philo, local_meals))
			break ;
		philo_think(philo);
		if (is_simulation_over(philo->config))
			break ;
		philo_eat(philo);
		if (is_simulation_over(philo->config))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
