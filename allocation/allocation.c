/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:57 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/05 20:55:58 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_allocation(t_philo *philo, char **av)
{
	int	i;
	int	*a;
	struct timeval current_time;

	i = -1;
	philo->n_philo = ft_atoi(av[1]);
	philo->lamp = 1;
	philo->t_die = ft_atoi(av[2]) * 1000;
	philo->t_eat = ft_atoi(av[3]) * 1000;
	philo->t_sleep = ft_atoi(av[4]) * 1000;
	philo->n_eat = ft_atoi(av[5]);
	philo->philos = malloc(sizeof(t_pthread) * philo->n_philo + 1);
	a = malloc(sizeof(int) * philo->n_philo);
	gettimeofday(&current_time, NULL);
	philo->time = current_time.tv_sec * 1e6 + current_time.tv_usec;
	while (++i <= philo->n_philo)
	{
		philo->philos[i].lamp = &philo->lamp;
		philo->philos[i].i = i + 1;
		philo->philos[i].n = philo->n_philo;
		philo->philos[i].forks = a;
		philo->philos[i].forks[i] = 1;
		philo->philos[i].n_eat = 0;
		philo->philos[i].all = philo;
		philo->philos[i].time = philo->time;	
	}
}