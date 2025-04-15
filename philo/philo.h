#ifndef PHILO_H
# define PHILO_H

//LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

//STRUCTURES
typedef struct s_simulation {
    int	num_philos;
    int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
} t_sim;

typedef struct s_philo {
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_sim			*sim;
	long			last_meal_time;
} t_philo;


/* FUNCTIONS */
void	start_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks);
void	*philo_routine(void *arg);
void	init_philosophers(pthread_mutex_t *fork, t_sim *sim, t_philo *philo);
pthread_mutex_t	*init_fork(int num);
ssize_t	ft_atoi(const char *str);
int initialization(int ac, char **av, t_sim *sim);

#endif