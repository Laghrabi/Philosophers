/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:12:12 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/20 13:18:07 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int sim_has_ended(t_sim *sim)
{
	int	end;

	pthread_mutex_lock(&sim->sim_mutex);
	end = sim->sim_end;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (end);
}

long	get_time(void)
{
	struct timeval	tv;
	long			ms;
	
	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	print_action(t_sim *sim, int id, char c)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (!sim_has_ended(sim) || c == 'd')
	{
		if (c == 'f')
			printf("%ld %d has taken a fork\n", (get_time() - sim->start_time), id);
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
