/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 01:08:54 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 17:01:25 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*handle_one_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", 0);
	usleep(philo->sim->time_to_die * 1000 + 10000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	*philo_loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_usleep(philo->sim->time_to_eat / 2, philo->sim);
	while (1)
	{
		pthread_mutex_lock(&philo->sim->sim_mutex);
		if (philo->sim->simulation_should_end)
		{
			pthread_mutex_unlock(&philo->sim->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->sim_mutex);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->num_philos == 1)
		return (handle_one_philosopher(philo));
	else
		return (philo_loop(philo));
}

int	start_simulation(t_sim *sim)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, &philo_routine,
				&sim->philos[i]) != 0)
			return (display_error("Failed to create the thread for philo"), 0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, sim) != 0)
		return (display_error("Failure to create monitor thread"), 0);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}
