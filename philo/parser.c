/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:32:50 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 16:56:31 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_sim *sim)
{
	if (sim->num_philos <= 0)
		return (display_error("The number of philosophers should be > 0"), 0);
	if (sim->time_to_die <= 0)
		return (display_error("time_to_die should be > 0"), 0);
	if (sim->time_to_eat <= 0)
		return (display_error("time_to_eat should be > 0"), 0);
	if (sim->time_to_sleep <= 0)
		return (display_error("time_to_sleep should be > 0"), 0);
	return (1);
}

static int	is_valid_number(const char *s)
{
	int	digit;

	digit = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			digit = 1;
		else
			return (0);
		s++;
	}
	return (digit);
}

int	parse_args(t_sim *sim, int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (display_error("Incorrect number of arguments"), 0);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (display_error("Argument contains invalid characters"), 0);
		i++;
	}
	sim->num_philos = (int)ft_atol(av[1]);
	sim->time_to_die = ft_atol(av[2]);
	sim->time_to_eat = ft_atol(av[3]);
	sim->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
	{
		sim->num_meals_to_eat = (int)ft_atol(av[5]);
		if (sim->num_meals_to_eat <= 0)
			return (display_error("num_meals_to_eat must be > 0"), 0);
	}
	else
		sim->num_meals_to_eat = -1;
	return (check_args(sim));
}
