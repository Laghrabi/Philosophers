/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:12:12 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:26:58 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if the simulation has ended.
 *
 * Locks sim_mutex, reads sim_end flag, unlocks, and returns its value.
 *
 * @param sim Pointer to the simulation structure.
 * @return 1 if simulation ended, 0 otherwise.
 */

int	sim_has_ended(t_sim *sim)
{
	int	end;

	pthread_mutex_lock(&sim->sim_mutex);
	end = sim->sim_end;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (end);
}

/**
 * @brief Gets the current timestamp in milliseconds.
 *
 * Uses gettimeofday() to return the time since Epoch in milliseconds.
 *
 * @return Current time in milliseconds.
 */

long	get_time(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

/**
 * @brief Cleans up and frees all allocated memory and destroys mutexes.
 *
 * Destroys each fork and philosopher mutex, simulation mutexes, 
 * and frees the arrays of forks and philosophers.
 *
 * @param forks Pointer to array of fork mutexes.
 * @param philo Pointer to array of philosopher structures.
 * @param sim Pointer to the simulation structure.
 */

void	clean_up(pthread_mutex_t *forks, t_philo *philo, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->sim_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	free(forks);
	free(philo);
}

/**
 * @brief Makes the philosopher sleep for time_to_sleep milliseconds.
 *
 * Prints sleeping action, sleeps, and a short extra delay for stability.
 *
 * @param philo Pointer to the philosopher structure.
 */

void	philo_sleep(t_philo *philo)
{
	print_action(philo->sim, philo->id, 's');
	usleep(philo->sim->time_to_sleep * 1000);
	usleep(500);
}

/**
 * @brief Prints an action of a philosopher with timestamp.
 *
 * Locks print_mutex to avoid mixed prints, prints the action based on
 * the character passed, and unlocks the mutex afterward.
 * Even if the simulation ended, 'd' (death) messages are still printed.
 *
 * @param sim Pointer to the simulation structure.
 * @param id Philosopher ID.
 * @param c Character representing the action:
 *          'f' = fork taken, 'e' = eating, 's' = sleeping,
 *          't' = thinking, 'd' = died.
 */

void	print_action(t_sim *sim, int id, char c)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (!sim_has_ended(sim) || c == 'd')
	{
		if (c == 'f')
			printf("%ld %d has taken a fork\n", (get_time() \
			- sim->start_time), id);
		else if (c == 'e')
			printf("%ld %d is eating\n", (get_time() - sim->start_time), id);
		else if (c == 's')
			printf("%ld %d is sleeping\n", (get_time() - sim->start_time), id);
		else if (c == 't')
			printf("%ld %d is thinking\n", (get_time() - sim->start_time), id);
		else
			printf("%ld %d died\n", (get_time() - sim->start_time), id);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}
