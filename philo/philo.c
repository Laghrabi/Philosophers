/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:09:32 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:24:57 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles eating for an even-numbered philosopher.
 *
 * Locks the left then right fork, updates last meal time,
 * prints actions, increments meals_eaten, and checks if done.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 0 if philosopher finished all meals, 1 otherwise.
 */

int	if_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->sim, philo->id, 'f');
	pthread_mutex_lock(philo->right_fork);
	print_action(philo->sim, philo->id, 'f');
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo->sim, philo->id, 'e');
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	if (philo->sim->times_must_eat != 0 && \
	philo->meals_eaten == philo->sim->times_must_eat)
	{
		philo->is_done = 1;
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

/**
 * @brief Handles eating for an odd-numbered philosopher.
 *
 * Locks the right then left fork, updates last meal time,
 * prints actions, increments meals_eaten, and checks if done.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 0 if philosopher finished all meals, 1 otherwise.
 */

int	if_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo->sim, philo->id, 'f');
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->sim, philo->id, 'f');
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo->sim, philo->id, 'e');
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	if (philo->sim->times_must_eat != 0 && \
	philo->meals_eaten == philo->sim->times_must_eat)
	{
		philo->is_done = 1;
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

/**
 * @brief Decides whether to use if_even() or if_odd() for eating.
 *
 * Calls the appropriate eating function based on philosopher ID parity.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 0 if philosopher finished all meals, 1 otherwise.
 */

int	perform_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (if_even(philo) == 0)
			return (0);
	}
	else
	{
		if (if_odd(philo) == 0)
			return (0);
	}
	return (1);
}

/**
 * @brief Verifies neighbors' meal counts before allowing philosopher to eat.
 *
 * Locks neighbors' meal_mutexes, checks if their meals match expected values,
 * unlocks the mutexes, and sleeps shortly if not ready.
 *
 * @param philo Pointer to the philosopher structure.
 * @param right Index of the right neighbor philosopher.
 * @param left Index of the left neighbor philosopher.
 * @return 1 if neighbors are ready, 0 otherwise.
 */

int	check_neighbors(t_philo *philo, int right, int left)
{
	int (ok);
	ok = 1;
	if (philo->id % 2 != 0 && philo->id == philo->sim->num_philos)
	{
		if (philo->philo_array[left].meals_eaten != philo->meals_eaten || \
		philo->philo_array[right].meals_eaten != philo->meals_eaten + 1)
			ok = 0;
	}
	else if (philo->id % 2 != 0)
	{
		if (philo->philo_array[left].meals_eaten != philo->meals_eaten || \
		philo->philo_array[right].meals_eaten != philo->meals_eaten)
			ok = 0;
	}
	else if (philo->id % 2 == 0)
	{
		if (philo->philo_array[left].meals_eaten != philo->meals_eaten + 1 || \
		philo->philo_array[right].meals_eaten != philo->meals_eaten + 1)
			ok = 0;
	}
	pthread_mutex_unlock(&philo->philo_array[left].meal_mutex);
	pthread_mutex_unlock(&philo->philo_array[right].meal_mutex);
	if (ok == 0)
		usleep(500);
	return (ok);
}

/**
 * @brief Main routine for each philosopher thread.
 *
 * Handles the philosopher's actions in a loop: thinking, checking neighbors,
 * eating, sleeping, and repeating until the simulation ends.
 *
 * @param arg Pointer to the philosopher structure (passed as void*).
 * @return NULL when the philosopher thread terminates.
 */

void	*philo_routine(void *arg)
{
	t_philo (*philo);
	int (i), (right), (left);
	philo = (t_philo *)arg;
	if (philo->sim->num_philos == 1)
		return (only_one(philo));
	i = 0;
	while (sim_has_ended(philo->sim) != 1)
	{
		if (i == 0)
			print_action(philo->sim, philo->id, 't');
		i = 1;
		left = (philo->id - 2 + philo->sim->num_philos) % \
		philo->sim->num_philos;
		right = (philo->id) % philo->sim->num_philos;
		lock_neighbors(philo, left, right);
		if (check_neighbors(philo, right, left) == 0)
			continue ;
		if (perform_eating(philo) == 0)
			return (NULL);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo);
		i = 0;
	}
	return (NULL);
}
