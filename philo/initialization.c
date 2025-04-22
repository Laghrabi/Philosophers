/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:41 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 12:25:39 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
