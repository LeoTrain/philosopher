#include "../../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_elapsed_time(long start_time)
{
	return (get_current_time() - start_time);
}

int	ft_usleep(long duration_ms, t_thread_data *thread_data)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < duration_ms)
	{
		if (someone_died(thread_data))
			return (1);
		usleep(500);
	}
	return (0);
}
