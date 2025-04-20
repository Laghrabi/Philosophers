/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:07:25 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/20 16:43:28 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if ((get_time() - philo->last_meal_time) > philo->sim->time_to_die && philo->is_done == 0)
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

int	handle_all_done(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_mutex);
    if (!sim->sim_end)
        sim->sim_end = 1;
    pthread_mutex_unlock(&sim->sim_mutex);
    return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	int all_done;

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
