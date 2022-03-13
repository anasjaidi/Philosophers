/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:57 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/10 14:57:02 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_allocation(t_philo *philo, char **av)
{
	int	i;

	i = -1;
	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	if (av[5])
		philo->n_eat = ft_atoi(av[5]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->philos = malloc(sizeof(t_pthread) * (philo->n_philo));
	if (!philo->philos)
		return (0);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n_philo);
	if (!philo->forks)
		return (free(philo->philos), 0);
	philo->time = get_time();
	while (++i < philo->n_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo->philos[i].i = i + 1;
		philo->philos[i].n_eat = 0;
		philo->philos[i].all = philo;
		philo->philos[i].time = philo->time;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3));
}

void	out(t_pthread *philo, char *s, int lamp)
{
	pthread_mutex_lock(&philo->all->mutex);
	if (s)
		printf("%lld philo %d %s\n", (get_time() - philo->all->time) \
		, philo->i, s);
	if (lamp)
		pthread_mutex_unlock(&philo->all->mutex);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	curr;

	curr = get_time();
	while (get_time() - curr < time)
		usleep(50);
}

int	ft_free(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
		pthread_mutex_destroy(&(philo->forks[i]));
	pthread_mutex_destroy(&(philo->mutex));
	free(philo->philos);
	free(philo->forks);
	return (0);
}
