/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:53:45 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/03 17:24:20 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	i = 0;
	while (i < sim->num_philos && sim->forks)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->write_mutex);
	pthread_mutex_destroy(&sim->sim_mutex);
	if (sim->philos)
		free(sim->philos);
	if (sim->forks)
		free(sim->forks);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	memset(&sim, 0, sizeof(t_sim));
	if (!parse_args(&sim, argc, argv))
		return (1);
	if (!init_simulation(&sim))
	{
		cleanup(&sim);
		return (1);
	}
	if (!start_simulation(&sim))
	{
		cleanup(&sim);
		return (1);
	}
	printf("-----Simulación Terminada-----\n");
	cleanup(&sim);
	return (0);
}
