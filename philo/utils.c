/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 08:26:19 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/02 02:16:46 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	display_error(char *message)
{
	if (write(2, "Error: ", 7) < 0
		|| write(2, message, ft_strlen(message)) < 0
		|| write(2, "\n", 1) < 0)
		return ;
}

void	print_status(t_philo *philo, const char *status, int force_print)
{
	long	timestam;
	int		sim_ended;

	pthread_mutex_lock(&philo->sim->write_mutex);
	timestam = get_time_since(philo->sim->start_time);
	pthread_mutex_lock(&philo->sim->sim_mutex);
	sim_ended = philo->sim->simulation_should_end;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	if (!sim_ended || force_print)
	{
		printf("%ld %d %s\n", timestam, philo->id, status);
	}
	pthread_mutex_unlock(&philo->sim->write_mutex);
}
