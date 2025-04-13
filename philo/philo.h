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
	int		id;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_sim			*sim;
} t_philo;


/* FUNCTIONS */
ssize_t	ft_atoi(const char *str);
int initialization(int ac, char **av, t_sim *sim);

#endif