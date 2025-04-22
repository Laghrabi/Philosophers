/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:36:02 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:21:46 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles the case when there is only one philosopher.
 *
 * The philosopher will think, pick up their only fork, wait until they die (sleep for time_to_die),
 * and then release the fork.
 *
 * @param philo Pointer to the philosopher structure.
 * @return NULL always, as the thread terminates.
 */

void	*only_one(t_philo *philo)
{
	print_action(philo->sim, philo->id, 't');
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->sim, philo->id, 'f');
	usleep(philo->sim->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

/**
 * @brief Locks the meal mutexes of the left and right neighbors in a safe order.
 *
 * To prevent deadlocks, the mutexes are always locked in ascending memory address order.
 *
 * @param philo Pointer to the current philosopher structure.
 * @param left Index of the left neighbor philosopher.
 * @param right Index of the right neighbor philosopher.
 */

void	lock_neighbors(t_philo *philo, int left, int right)
{
	if (&philo->philo_array[left].meal_mutex \
		< &philo->philo_array[right].meal_mutex)
	{
		pthread_mutex_lock(&philo->philo_array[left].meal_mutex);
		pthread_mutex_lock(&philo->philo_array[right].meal_mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->philo_array[right].meal_mutex);
		pthread_mutex_lock(&philo->philo_array[left].meal_mutex);
	}
}

/**
 * @brief Initializes the simulation settings and philosophers.
 *
 * Initializes global simulation mutexes, assigns forks to philosophers, sets start time,
 * and initializes each philosopher's meal mutex and last meal time.
 *
 * @param sim Pointer to the simulation structure.
 * @param philo Pointer to the array of philosopher structures.
 * @param forks Pointer to the array of fork mutexes.
 */

void	init_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_init(&sim->sim_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	init_philosophers(forks, sim, philo);
	sim->start_time = get_time();
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].last_meal_time = sim->start_time;
		i++;
	}
}

/**
 * @brief Starts the philosophers' simulation.
 *
 * Initializes the simulation, creates a thread for each philosopher and a monitor thread,
 * waits for all threads to finish, and joins them.
 *
 * @param sim Pointer to the simulation structure.
 * @param philo Pointer to the array of philosopher structures.
 * @param forks Pointer to the array of fork mutexes.
 */

void	start_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	monitor_thread;

	init_simulation(sim, philo, forks);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor_routine, (void *)philo);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

/**
 * @brief Main entry point of the program.
 *
 * Parses arguments, initializes the simulation, allocates memory for forks and philosophers,
 * starts the simulation, and finally frees all allocated resources.
 *
 * @param ac Argument count.
 * @param av Argument values.
 * @return 0 on success, 1 on error.
 */

int	main(int ac, char **av)
{
	t_sim			sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6)
		return (0);
	if (initialization(ac, av, &sim) == -1)
	{
		return (1);
	}
	forks = init_fork(sim.num_philos);
	if (forks == NULL)
		return (1);
	philo = malloc(sizeof(t_philo) * sim.num_philos);
	if (philo == NULL)
	{
		free(forks);
		return (1);
	}
	start_simulation(&sim, philo, forks);
	clean_up(forks, philo, &sim);
	return (0);
}
