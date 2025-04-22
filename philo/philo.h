/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:43:09 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/22 12:23:51 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//LIBRARIES
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//STRUCTURES
typedef struct s_philo	t_philo;

typedef struct s_simulation
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
	long				start_time;
	int					sim_end;
	pthread_mutex_t		sim_mutex;
	pthread_mutex_t		print_mutex;
}						t_sim;

typedef struct s_philo
{
	int					id;
	int					is_done;
	int					meals_eaten;
	pthread_t			thread;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		meal_mutex;
	t_sim				*sim;
	long				last_meal_time;
	t_philo				*philo_array;
}						t_philo;

/* FUNCTIONS */
int						sim_has_ended(t_sim *sim);
int						if_even(t_philo *philo);
int						if_odd(t_philo *philo);
int						perform_eating(t_philo *philo);
int						initialization(int ac, char **av, t_sim *sim);
int						check_neighbors(t_philo *philo, int right, int left);
int						check_if_all_done(t_philo *philo, t_sim *sim);
int						check_philo_death(t_philo *philo);
int						sim_has_ended(t_sim *sim);
int						handle_all_done(t_sim *sim);
void					print_action(t_sim *sim, int id, char c);
void					clean_up(pthread_mutex_t *forks, t_philo *philo,
							t_sim *sim);
void					*only_one(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					lock_neighbors(t_philo *philo, int left, int right);
void					start_simulation(t_sim *sim, t_philo *philo,
							pthread_mutex_t *forks);
void					*monitor_routine(void *arg);
void					start_simulation(t_sim *sim, t_philo *philo,
							pthread_mutex_t *forks);
void					*philo_routine(void *arg);
void					init_philosophers(pthread_mutex_t *fork, t_sim *sim,
							t_philo *philo);
long					get_time(void);
ssize_t					ft_atoi(const char *str);
pthread_mutex_t			*init_fork(int num);
pthread_mutex_t			*init_fork(int num);

#endif