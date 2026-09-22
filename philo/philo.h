/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:59:08 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 02:16:21 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// Estructura para los filosofos.
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eating;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_sim	*sim;
}					t_philo;

// Estructura para la simulacion.
typedef struct s_sim
{
	int				num_philos;
	int				num_meals_to_eat;
	int				simulation_should_end;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;

	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	sim_mutex;

}					t_sim;

// time.c

long				get_current_time(void);
void				precise_usleep(long time_in_ms, t_sim *sim);
long				get_time_since(long start_time);

// utils.c

void				print_status(t_philo *philo, const char *status,
						int force_print);
void				display_error(char *message);
long				ft_atol(const char *str);
size_t				ft_strlen(char *s);

// Parser.c

int					parse_args(t_sim *sim, int ac, char **av);

// init.c

int					init_simulation(t_sim *sim);

// main.c

int					main(int ac, char **av);

// Simulation.c

void				*philo_routine(void *arg);
int					start_simulation(t_sim *sim);

// Monitor.c

void				*monitor_routine(void *arg);

// actions.c

void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

#endif
