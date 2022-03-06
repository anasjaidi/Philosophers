/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabani <asabani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:29:41 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/06 22:46:20 by asabani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	mutex;

void out(int i, char *s)
{
	pthread_mutex_lock(&mutex);
	printf("philo %d %s\n", i, s);
	pthread_mutex_unlock(&mutex);
}

void	*func(void *ph)
{
	t_pthread *philo;
	struct timeval current_time;
	//int i =0;
	
	philo = ph;
	if (!(philo->i & 1))
		usleep(philo->all->t_eat * 1e3);
	while (1)
	{
		pthread_mutex_lock(&philo->forks[(philo->i - 1 ) % philo->n]);
		out(philo->i , "taken a fork");
		pthread_mutex_lock(&philo->forks[(philo->i) % philo->n]);
		out(philo->i , "taken a fork");
		out(philo->i , "is eating");
		usleep(philo->all->t_eat * 1e3);
		pthread_mutex_unlock(&philo->forks[(philo->i - 1 ) % philo->n]);
		pthread_mutex_unlock(&philo->forks[(philo->i) % philo->n]);
		gettimeofday(&current_time, NULL);
		philo->time = (current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3);
		out(philo->i, "is sleeping");
		usleep(philo->all->t_sleep * 1e3);
		out(philo->i, "is thinking");
	}
	
	return (ph);
}

void	*manager(void *ph)
{
	t_philo *philo;
	struct timeval current_time;

	philo = ph;
	int i = 0;
	while (1)
	{
		if (i == philo->n_philo)
			i = 0;
		gettimeofday(&current_time, NULL);
		if (((current_time.tv_sec * 1e3) + (current_time.tv_usec / 1e3)) - philo->philos[i].time > (philo->t_die))
			philo->lamp = 0;
		i++;
	}
	
}

void	ft_thread(t_philo *philo)
{
	int	i;

	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < philo->n_philo )
		pthread_create(&philo->philos[i].philo , NULL, func, &philo->philos[i]);
	pthread_create(&philo->philos[i].philo , NULL, manager, philo);
	i = -1;
	while (++i < philo->n_philo)
		pthread_detach(philo->philos[i].philo);
	// while (++i < philo->n_philo + 1)
	// {
	// 	printf("is %d\n",philo->philos[i].i);
	// }
}