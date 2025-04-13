/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:41 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/13 21:45:58 by claghrab         ###   ########.fr       */
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
		philo->id = i + 1;
		philo->sim = sim;
		philo->left_fork = &fork[i];
		philo->right_fork = &fork[(i + 1) % sim->num_philos];
		i++;
	}
}
