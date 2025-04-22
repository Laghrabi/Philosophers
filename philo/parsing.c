/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:34:44 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 12:46:22 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	ft_atoi(const char *str)
{
	int (i), (sign);
	ssize_t (result);
	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		result = result * 10 + (str[i] - '0');
		if (result > (ssize_t)INT_MAX + sign)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
	{
		return (-1);
	}
	return (result * sign);
}

int	initialization(int ac, char **av, t_sim *sim)
{
	sim->sim_end = 0;
	sim->num_philos = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		sim->times_must_eat = ft_atoi(av[5]);
	else
		sim->times_must_eat = 0;
	if (sim->num_philos < 0 || sim->time_to_die < 0 || sim->time_to_eat < 0
		|| sim->time_to_sleep < 0 || sim->times_must_eat < 0)
	{
		printf("Wrong Arguments\n");
		return (-1);
	}
	return (0);
}
