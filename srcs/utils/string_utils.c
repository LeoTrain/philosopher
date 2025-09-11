#include "../../includes/philo.h"

int	is_number(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (*str < '0' || *str > '9')
		return (FAILURE);
	while (*str >= '0' && *str <= '9')
		str++;
	while (*str == ' ')
		str++;
	if (*str == '\0')
		return (SUCCESS);
	return (FAILURE);
}

int	ft_atoi(char *str)
{
	long	result;
	int		sign;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return ((int)(result * sign));
}

long	ft_atol(char *str)
{
	long long	result;
	int		sign;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return ((long)(result * sign));
}
