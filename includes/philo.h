/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:50:41 by leberton          #+#    #+#             */
/*   Updated: 2025/12/30 14:52:07 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"

int				is_simulation_over(t_simulation_config *config);
void			stop_simulation(t_simulation_config *config);
t_error_code	print_philo_action(t_philo *philo, const char *action);

long			get_time_ms(void);
void			precise_sleep_ms(long duration_ms, t_simulation_config *config);

t_error_code	str_is_all_digits(char *str);
t_error_code	parse_positive_long(const char *str, long *out);
t_error_code	validate_all_args(int argc, char **argv);

t_error_code	take_forks(t_philo *philo);
t_error_code	release_forks(t_philo *philo);

t_error_code	update_meal_time(t_philo *philo);
t_error_code	philo_eat(t_philo *philo);
t_error_code	philo_think(t_philo *philo);
t_error_code	philo_sleep(t_philo *philo);

t_error_code	init_simulation_config(int argc, char **argv,
					t_simulation_config *config);

t_error_code	init_fork_mutexes(t_simulation *sim);

t_error_code	init_philosophers(t_simulation *sim);

void			cleanup_simulation(t_simulation *sim, int init_level);

int				check_meal_goal_reached(t_simulation *sim);
void			*death_monitor_loop(void *arg);

void			*philo_lifecycle(void *arg);

t_error_code	init_start_time(t_simulation *sim);
t_error_code	create_philo_threads(t_simulation *sim);
t_error_code	create_death_monitor(t_simulation *sim);
t_error_code	join_all_threads(t_simulation *sim);

#endif
