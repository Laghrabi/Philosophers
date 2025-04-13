/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:36:02 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/13 22:03:43 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d is thinking 🍝\n", philo->id);
	return (NULL);
}

int main(int ac, char **av)
{
    int				i;
    t_sim			sim;
    t_philo			*philo;
    pthread_mutex_t	*forks;
    
    if (ac < 5 || ac > 6)
        return (0);
    if (initialization(ac, av, &sim) == -1)
        return (1);
    forks = init_fork(sim.num_philos);
	philo = malloc(sizeof(pthread_t) * sim.num_philos);
	init_philosophers(forks, &sim, philo);
	i = 0;
	while (i < sim.num_philos)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < sim.num_philos)
	{
		pthread_join(&philo[i].thread, NULL);
		i++;
	}
    return (0);   
}
