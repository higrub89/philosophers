/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 08:25:53 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 17:01:49 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Error: gettimeofday Failed\n");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_time_since(long start_time)
{
	return (get_current_time() - start_time);
}

void	precise_usleep(long time_in_ms, t_sim *sim)
{
	long	start_time;
	long	wake_up_time;

	start_time = get_current_time();
	wake_up_time = start_time + time_in_ms;
	while (get_current_time() < wake_up_time)
	{
		pthread_mutex_lock(&sim->sim_mutex);
		if (sim->simulation_should_end)
		{
			pthread_mutex_unlock(&sim->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&sim->sim_mutex);
		usleep(500);
	}
}
