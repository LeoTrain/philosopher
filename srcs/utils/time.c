/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:51:05 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:51:23 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	precise_sleep_ms(long duration_ms, t_simulation_config *config)
{
	long	start;
	long	target;
	long	remaining;

	start = get_time_ms();
	target = start + duration_ms;
	while (get_time_ms() < target)
	{
		if (is_simulation_over(config))
			return ;
		remaining = target - get_time_ms();
		if (remaining > 1)
			usleep(500);
		else
			usleep(100);
	}
}
