/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claghrab <claghrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:36:02 by claghrab          #+#    #+#             */
/*   Updated: 2025/04/13 15:46:02 by claghrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_sim sim;
    
    if (ac < 5 || ac > 6)
        return (0);
    if (initialization(ac, av, &sim) == -1)
        return (1);
    printf("%d %d %d %d %d\n", sim.num_philos, sim.time_to_die, sim.time_to_eat, sim.time_to_sleep, sim.times_must_eat);
    return (0);   
}