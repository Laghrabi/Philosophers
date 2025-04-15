/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:41 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/15 15:37:41 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_fork(int num)
{
    int				i;
    pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t) * num);
	if (fork == NULL)
		return (NULL);
    i = 0;
    while (i < num)
    {
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void	init_philosophers(pthread_mutex_t *fork, t_sim *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].sim = sim;
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % sim->num_philos];
		i++;
	}
}
