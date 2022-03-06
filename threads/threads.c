/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:29:41 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/05 20:53:08 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	mutex;

void	*func(void *ph)
{
	t_pthread *philo;
	struct timeval current_time;
	//int i =0;
	
	philo = ph;
	if (!(philo->i & 1))
		usleep(1000);
	while (1)
	{
		if (!philo->forks[(philo->i -1) % philo->n - 1] && !philo->forks[philo->i % philo->n])
			break ;
		pthread_mutex_lock(&mutex);
		philo->forks[(philo->i -1) % philo->n] = 0;
		philo->forks[philo->i % philo->n] = 0;
		printf("philo %d get forks\n", philo->i);
		usleep(philo->all->t_eat);
		philo->forks[philo->i % philo->n - 1] = 1;
		philo->forks[philo->i % philo->n] = 1;
		pthread_mutex_unlock(&mutex);
		gettimeofday(&current_time, NULL);
		philo->time = current_time.tv_sec * 1e6 + current_time.tv_usec ;
		printf("philo %d has sleeping\n", philo->i);
		usleep(philo->all->t_sleep);
		printf("philo %d has thinking\n", philo->i);
	}
	
	return (ph);
}

void	*manager(void *ph)
{
	t_philo *philo;
	struct timeval cu_t;

	philo = ph;
	int i = 0;
	while (1)
	{
		if (i == philo->n_philo)
			i = 0;
		gettimeofday(&cu_t, NULL);
		if ((cu_t.tv_sec * 1e6 + cu_t.tv_usec) - philo->philos[i].time >= (philo->t_die))
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