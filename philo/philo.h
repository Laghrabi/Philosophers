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


/* FUNCTIONS */
ssize_t	ft_atoi(const char *str);
int initialization(int ac, char **av, t_sim *sim);

#endif