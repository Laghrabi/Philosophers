/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:36:02 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/18 19:01:56 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			ms;
	
	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	print_action(t_sim *sim, long ms, int id, char c)
{
	pthread_mutex_lock(&sim->print_mutex);
	if (!sim_has_ended(sim) || c == 'd')
	{
		if (c == 'f')
			printf("%ld %d has taken a fork\n", ms, id);
		else if (c == 'e')
			printf("%ld %d is eating\n", ms, id);
		else if (c == 's')
			printf("%ld %d is sleeping\n", ms, id);
		else if (c == 't')
			printf("%ld %d is thinking\n", ms, id);
		else
			printf("%ld %d died\n", ms, id);
	}
	pthread_mutex_unlock(&sim->print_mutex);
}

// int	times_must_eat(t_philo *philo, int meals_eaten)
// {
// 	while (i < philo->sim->num_philos)
// 	{
// 		if (meals_eaten != philo->sim->times_must_eat)
			
// 	}
// }

// int	still_alive(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->meal_mutex);
// 	if ((get_time() - philo->last_meal_time) > philo->sim->time_to_die)
// 	{
// 		print_action((get_time() - philo->sim->start_time), philo->id, 'd');
// 		pthread_mutex_unlock(&philo->meal_mutex);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->meal_mutex);
// 	return (1);
// }

int sim_has_ended(t_sim *sim)
{
	int	end;

	pthread_mutex_lock(&sim->sim_mutex);
	end = sim->sim_end;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (end);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
    	usleep(philo->sim->time_to_eat * 1000);
	while (sim_has_ended(philo->sim) != 1)
	{
		print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 't');
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'f');
			pthread_mutex_lock(philo->right_fork);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'f');
			pthread_mutex_lock(&philo->meal_mutex);
			//printf("Philo_id= %d last_meal_time= %ld\n", philo->id, philo->last_meal_time);
			philo->last_meal_time = get_time();
			//printf("Philo_id= %d last_meal_time= %ld\n", philo->id, philo->last_meal_time);
			pthread_mutex_unlock(&philo->meal_mutex);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'e');
			usleep(philo->sim->time_to_eat * 1000);
			if (philo->sim->times_must_eat != 0)
			{
				philo->meals_eaten++;
				if (philo->meals_eaten == philo->sim->times_must_eat)
				{
					printf("id= %d meals_eaten= %d\n", philo->id, philo->meals_eaten);
					philo->is_done = 1;
					pthread_mutex_unlock(philo->left_fork);
					pthread_mutex_unlock(philo->right_fork);
					return (NULL);
				}
			}
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'f');
			pthread_mutex_lock(philo->left_fork);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'f');
			pthread_mutex_lock(&philo->meal_mutex);
			//printf("Philo_id= %d last_meal_time= %ld\n", philo->id, philo->last_meal_time);
			philo->last_meal_time = get_time();
			//printf("Philo_id= %d last_meal_time= %ld\n", philo->id, philo->last_meal_time);
			pthread_mutex_unlock(&philo->meal_mutex);
			print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 'e');
			usleep(philo->sim->time_to_eat * 1000);
			if (philo->sim->times_must_eat != 0)
			{
				philo->meals_eaten++;
				if (philo->meals_eaten == philo->sim->times_must_eat)
				{
					printf("id= %d meals_eaten= %d\n", philo->id, philo->meals_eaten);
					philo->is_done = 1;
					pthread_mutex_unlock(philo->left_fork);
					pthread_mutex_unlock(philo->right_fork);
					return (NULL);
				}
			}
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo->sim, (get_time() - philo->sim->start_time), philo->id, 's');
		usleep(philo->sim->time_to_sleep * 1000);
		usleep(500);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_sim	*sim;
	long	current_time;
	int		i;
	int all_done;

	philo = (t_philo *)arg;
	sim = philo[0].sim;
	usleep(sim->time_to_eat * 1000 + 5000);
	while (!sim_has_ended(sim))
	{
		i = 0;
		all_done = 1;
		while (i < sim->num_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			current_time = get_time();
			if ((current_time - philo[i].last_meal_time) > philo[i].sim->time_to_die && philo[i].is_done == 0)
			{
				//printf("Philo= %d current_time= %ld last_meal_time= %ld time_to_die= %d, diff= %ld\n", philo[i].id, current_time, philo[i].last_meal_time, philo[i].sim->time_to_die, current_time - philo[i].last_meal_time);
				pthread_mutex_lock(&sim->sim_mutex);
				if (!sim->sim_end)
				{
				sim->sim_end = 1;
				pthread_mutex_unlock(&sim->sim_mutex);
				print_action(philo->sim, get_time() - sim->start_time, philo[i].id, 'd');
				pthread_mutex_unlock(&philo[i].meal_mutex);
				return (NULL);
				}
				pthread_mutex_unlock(&sim->sim_mutex);
			}
			if (sim->times_must_eat > 0 && philo[i].is_done == 0)
                all_done = 0;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			i++;
		}
		if (sim->times_must_eat > 0 && all_done)
        {
            pthread_mutex_lock(&sim->sim_mutex);
            if (!sim->sim_end)
            {
                sim->sim_end = 1;
                printf("All philosophers have eaten %d times. Simulation complete.\n", sim->times_must_eat);
            }
            pthread_mutex_unlock(&sim->sim_mutex);
            return (NULL);
        }
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;
	pthread_t	monitor_thread;

	pthread_mutex_init(&sim->sim_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	init_philosophers(forks, sim, philo);
	sim->start_time = get_time();
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		philo[i].last_meal_time = sim->start_time;
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	usleep(500);
	pthread_create(&monitor_thread, NULL, monitor_routine, (void *)philo);
	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int main(int ac, char **av)
{
	t_sim			sim;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	// sim.start_time = get_time();
	//printf("%ld\n", sim.start_time);
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
		return (1);
	start_simulation(&sim, philo, forks);
    return (0);   
}
