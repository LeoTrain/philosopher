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