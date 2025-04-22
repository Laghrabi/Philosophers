/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:07:25 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 14:23:02 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks if a philosopher has died.
 *
 * Locks the philosopher's meal mutex to safely check if the time
 * since their last meal exceeds the allowed time_to_die. If so,
 * sets the simulation end flag and prints the death event.
 *
 * @param philo Pointer to the philosopher structure.
 * @return 0 if the philosopher died, 1 otherwise.
 */

int	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if ((get_time() - philo->last_meal_time) > \
	philo->sim->time_to_die && philo->is_done == 0)
	{
		pthread_mutex_lock(&philo->sim->sim_mutex);
		if (!philo->sim->sim_end)
		{
			philo->sim->sim_end = 1;
			pthread_mutex_unlock(&philo->sim->sim_mutex);
			print_action(philo->sim, philo->id, 'd');
			pthread_mutex_unlock(&philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->sim->sim_mutex);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (1);
}

/**
 * @brief Checks if all philosophers have finished eating or if any philosopher died.
 *
 * Iterates through all philosophers, checking for deaths using check_philo_death().
 * Also checks if each philosopher has finished the required number of meals.
 *
 * @param philo Pointer to the array of philosopher structures.
 * @param sim Pointer to the simulation structure.
 * @return 1 if all philosophers are done, 0 if simulation should continue.
 */

int	check_if_all_done(t_philo *philo, t_sim *sim)
{
	int (i), (all_done);
	i = 0;
	all_done = 1;
	while (i < sim->num_philos)
	{
		if (check_philo_death(&philo[i]) == 0)
			return (0);
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (sim->times_must_eat > 0 && philo[i].is_done == 0)
			all_done = 0;
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (all_done);
}

/**
 * @brief Safely marks the simulation as ended when all philosophers are done.
 *
 * Locks the simulation mutex and sets the sim_end flag to 1 if it is not already set.
 *
 * @param sim Pointer to the simulation structure.
 * @return Always returns 0 (success).
 */

int	handle_all_done(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_mutex);
	if (!sim->sim_end)
		sim->sim_end = 1;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (0);
}

/**
 * @brief Monitoring routine that constantly checks philosophers' statuses.
 *
 * A thread running this function will periodically check if any philosopher has died
 * or if all philosophers have completed the required number of meals. 
 * If a philosopher dies or all are done, the simulation ends.
 *
 * @param arg Pointer to the first philosopher structure (used to get sim pointer too).
 * @return NULL when the monitoring thread terminates.
 */

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int		all_done;

	philo = (t_philo *)arg;
	sim = philo[0].sim;
	usleep(sim->time_to_eat * 1000 + 5000);
	while (!sim_has_ended(sim))
	{
		all_done = check_if_all_done(philo, sim);
		if (sim->times_must_eat > 0 && all_done)
		{
			if (handle_all_done(sim) == 0)
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
