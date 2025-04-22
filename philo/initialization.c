/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:41 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:20:00 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Allocates and initializes an array of mutexes to represent forks.
 * 
 * This function dynamically allocates memory for the specified number of forks
 * and initializes each one using pthread_mutex_init.
 * 
 * @param num The number of forks (equal to the number of philosophers).
 * @return A pointer to the allocated and initialized array of mutexes, 
 *         or NULL if the memory allocation fails.
 */

pthread_mutex_t	*init_fork(int num)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * num);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

/**
 * @brief Initializes the philosophers' data structures.
 * 
 * Each philosopher is assigned an ID, a left fork, a right fork, a reference 
 * to the shared simulation structure, and a reference to the full philosophers array.
 * The 'is_done' flag is initially set to 0 for each philosopher.
 *
 * @param fork Pointer to the array of forks (mutexes).
 * @param sim Pointer to the simulation structure containing simulation parameters.
 * @param philo Pointer to the array of philosopher structures to initialize.
 */

void	init_philosophers(pthread_mutex_t *fork, t_sim *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].is_done = 0;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % sim->num_philos];
		philo[i].sim = sim;
		philo[i].philo_array = philo;
		i++;
	}
}
