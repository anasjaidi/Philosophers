/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:57 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/07 23:29:19 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_allocation(t_philo *philo, char **av)
{
	int	i;

	i = -1;
	philo->n_philo = ft_atoi(av[1]);
	philo->lamp = 1;
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->n_eat = ft_atoi(av[5]);
	philo->philos = malloc(sizeof(t_pthread) * (philo->n_philo + 1));
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	philo->time = get_time();
	while (++i < philo->n_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->philos[i].i = i + 1;
		philo->philos[i].n_eat = 0;
		philo->philos[i].all = philo;
		philo->philos[i].time = philo->time;
	}
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

void	check_lamp(int ac, t_philo *philo)
{
	if (ac == 5)
		philo->lamp = 0;
	else
		philo->lamp = 1;
}
