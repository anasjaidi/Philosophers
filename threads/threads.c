/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:29:41 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/07 23:36:13 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	out(long long time, t_pthread *philo, char *s)
{
	pthread_mutex_lock(&philo->all->mutex);
	printf("%lld philo %d %s\n", time, philo->i, s);
	pthread_mutex_unlock(&philo->all->mutex);
}

void	sets_fork(t_pthread *philo, int x)
{
	if (x == 0)
	{
		pthread_mutex_lock(&philo->all->forks[(philo->i - 1) \
			% philo->all->n_philo]);
		out((get_time() - philo->all->time), philo, "taken a fork");
		pthread_mutex_lock(&philo->all->forks[(philo->i) \
			% philo->all->n_philo]);
		out((get_time() - philo->all->time), philo, "taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->all->forks[(philo->i - 1) \
			% philo->all->n_philo]);
		pthread_mutex_unlock(&philo->all->forks[(philo->i) \
			% philo->all->n_philo]);
	}
}

void	*func(void *ph)
{
	t_pthread	*philo;
	int			*ptr;

	philo = ph;
	ptr = &philo->all->lamp;
	if (!(philo->i & 1))
		usleep(philo->all->t_eat * 1e3);
	while (1)
	{
		if (philo->n_eat == philo->all->n_eat && philo->all->lamp)
			*ptr = 2;
		sets_fork(philo, 0);
		out((get_time() - philo->all->time), philo, "is eating");
		philo->n_eat += 1;
		usleep(philo->all->t_eat * 1e3);
		sets_fork(philo, 1);
		philo->time = get_time();
		out((get_time() - philo->all->time), philo, "is sleeping");
		usleep(philo->all->t_sleep * 1e3);
		out((get_time() - philo->all->time), philo, "is thinking");
	}
}

void	*manager(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->lamp != 2)
	{
		if (i == philo->n_philo)
			i = 0;
		if ((get_time() - philo->philos[i].time) > philo->t_die)
		{
			out(get_time() - philo->time, &philo->philos[i], "has died");
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	ft_thread(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_init(&philo->mutex, NULL);
	while (++i < philo->n_philo)
		pthread_create(&philo->philos[i].philo, NULL, func, &philo->philos[i]);
	i = -1;
	while (++i < philo->n_philo)
		pthread_detach(philo->philos[i].philo);
}
