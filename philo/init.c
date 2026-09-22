/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:53:27 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 17:05:20 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (display_error("Failed to initialize mutex fork"), 0);
		i++;
	}
	if (pthread_mutex_init(&sim->write_mutex, NULL) != 0)
		return (display_error("Failed to initialize mutex write"), 0);
	if (pthread_mutex_init(&sim->sim_mutex, NULL) != 0)
		return (display_error("Failed to initialize mutex simulation"), 0);
	return (1);
}

static void	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].sim = sim;
		sim->philos[i].meals_eating = 0;
		sim->philos[i].last_meal_time = sim->start_time;
		sim->philos[i].left_fork = &sim->forks[i];
		if (i == sim->num_philos - 1)
			sim->philos[i].right_fork = &sim->forks[0];
		else
			sim->philos[i].right_fork = &sim->forks[i + 1];
		i++;
	}
}

int	init_simulation(t_sim *sim)
{
	sim->philos = malloc(sizeof(t_philo) * sim->num_philos);
	if (!sim->philos)
		return (display_error("Malloc failed for philosophers"), 0);
	memset(sim->philos, 0, sizeof(t_philo) * sim->num_philos);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (!sim->forks)
		return (free(sim->philos), display_error("Malloc failed for forks"),
			0);
	if (!init_mutex(sim))
	{
		free(sim->philos);
		free(sim->forks);
		return (0);
	}
	sim->start_time = get_current_time();
	init_philos(sim);
	return (1);
}
