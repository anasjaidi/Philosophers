/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:29:41 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/11 15:33:05 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sets_fork(t_pthread *philo, int x)
{
	if (x == 0)
	{
		pthread_mutex_lock(&philo->all->forks[(philo->i - 1) \
			% philo->all->n_philo]);
		out(philo, "taken a fork", 1);
		pthread_mutex_lock(&philo->all->forks[(philo->i) \
			% philo->all->n_philo]);
		out(philo, "taken a fork", 1);
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

	philo = ph;
	if (!(philo->i & 1))
		ft_usleep(philo->all->t_eat / 2);
	while (1)
	{
		sets_fork(philo, 0);
		out(philo, "is eating", 1);
		ft_usleep(philo->all->t_eat);
		sets_fork(philo, 1);
		philo->time = get_time();
		out(philo, "is sleeping", 1);
		ft_usleep(philo->all->t_sleep);
		out(philo, "is thinking", 1);
		philo->n_eat += 1;
	}
}

void	*manager(t_philo *philo)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (1)
	{
		if (i == philo->n_philo)
		{
			i = 0;
			c = 0;
		}
		if (philo->n_eat)
			if (!n_eat(&c, &philo->philos[i]))
				return (NULL);
		if ((get_time() - philo->philos[i].time) >= philo->t_die)
		{
			out(&philo->philos[i], "died", 0);
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

int	n_eat(int *c, t_pthread *philo)
{
	if (philo->n_eat >= philo->all->n_eat)
		*c += 1;
	if (*c == philo->all->n_philo)
	{
		out(philo, NULL, 0);
		return (0);
	}
	return (1);
}
