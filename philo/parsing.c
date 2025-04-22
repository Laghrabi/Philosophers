/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:34:44 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:18:46 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts a string to a signed size_t integer.
 * 
 * The function skips leading whitespace characters, handles an optional '+' or '-' sign,
 * and then converts the following digit characters into an integer value.
 * If the string contains invalid characters or the number overflows, it returns -1.
 *
 * @param str The string to convert.
 * @return The converted integer value on success, or -1 on error (invalid input or overflow).
 */

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

/**
 * @brief Initializes the simulation parameters from command-line arguments.
 * 
 * Parses and validates the arguments to fill the t_sim structure with the number of philosophers,
 * time to die, time to eat, time to sleep, and optional number of times each philosopher must eat.
 * 
 * @param ac The argument count.
 * @param av The argument vector (array of strings).
 * @param sim Pointer to the simulation structure to initialize.
 * @return 0 on success, -1 if an error occurs (invalid or negative argument values).
 */

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
