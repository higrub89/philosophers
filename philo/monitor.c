/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:04:46 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 16:04:57 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_philo_died(t_philo *philo)
{
	long	current_time;
	int		died;

	died = 0;
	pthread_mutex_lock(&philo->sim->sim_mutex);
	current_time = get_current_time();
	if (current_time - philo->last_meal_time >= philo->sim->time_to_die
		&& !philo->sim->simulation_should_end)
	{
		philo->sim->simulation_should_end = 1;
		died = 1;
	}
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	if (died)
	{
		print_status(philo, "died", 1);
		return (1);
	}
	return (0);
}

static int	have_all_eaten(t_sim *sim)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	if (sim->num_meals_to_eat == -1)
		return (0);
	pthread_mutex_lock(&sim->sim_mutex);
	i = 0;
	while (i < sim->num_philos)
	{
		if (sim->philos[i].meals_eating < sim->num_meals_to_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	if (all_ate)
		sim->simulation_should_end = 1;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (all_ate);
}

static int	check_death_and_meals(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (has_philo_died(&sim->philos[i]))
			return (1);
		i++;
	}
	if (have_all_eaten(sim))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	usleep(sim->time_to_die / 2 * 1000);
	while (1)
	{
		if (check_death_and_meals(sim))
			break ;
		usleep(1000);
	}
	return (NULL);
}
