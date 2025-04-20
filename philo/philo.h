#ifndef PHILO_H
# define PHILO_H

//LIBRARIES
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

//STRUCTURES
typedef struct s_philo t_philo;

typedef struct s_simulation {
    int	num_philos;
    int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
	long	start_time;
	int	sim_end;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	print_mutex;
} t_sim;

typedef struct s_philo {
	int				id;
	int				is_done;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	meal_mutex;
	t_sim			*sim;
	long			last_meal_time;
	t_philo *philo_array;
} t_philo;


/* FUNCTIONS */
int sim_has_ended(t_sim *sim);
long	get_time(void);
void	print_action(t_sim *sim, int id, char c);
int	if_even(t_philo *philo);
int	if_odd(t_philo *philo);
int	perform_eating(t_philo *philo);
int	check_neighbors(t_philo *philo, int right, int left);
pthread_mutex_t	*init_fork(int num);
void	*only_one(t_philo *philo);
void philo_sleep(t_philo *philo);
void	lock_neighbors(t_philo *philo, int left, int right);
void	start_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks);
void	*monitor_routine(void *arg);
int	handle_all_done(t_sim *sim);
int	check_if_all_done(t_philo *philo, t_sim *sim);
int	check_philo_death(t_philo *philo);
int sim_has_ended(t_sim *sim);
void	start_simulation(t_sim *sim, t_philo *philo, pthread_mutex_t *forks);
void	*philo_routine(void *arg);
void	init_philosophers(pthread_mutex_t *fork, t_sim *sim, t_philo *philo);
pthread_mutex_t	*init_fork(int num);
ssize_t	ft_atoi(const char *str);
int initialization(int ac, char **av, t_sim *sim);

#endif