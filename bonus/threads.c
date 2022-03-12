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

void	out(t_pthread *philo, char *s, int lamp)
{
	sem_wait(philo->all->printf);
	printf("%lld philo %d %s\n", (get_time() - philo->all->time), philo->i, s);
	if (lamp)
		sem_post(philo->all->printf);
}

void	sets_fork(t_pthread *philo, int x)
{
	if (x == 0)
	{
		sem_wait(philo->all->robin);
		out(philo, "taken a fork", 1);
		sem_wait(philo->all->robin);
		out(philo, "taken a fork", 1);
	}
	else
	{
		sem_post(philo->all->robin);
		sem_post(philo->all->robin);
	}
}

void	*manager(void *ph)
{
	while (1)
	{
		if (philo->all->n_eat)
			if (philo->n_eat >= philo->all->n_eat)
				c++;
		if ((get_time() - philo->time) >= philo->all->t_die + 5)
		{
			out(&philo->philos[i], "died", 0);
			ft_exit(pid, philo);
		}
	}
}

void	func(t_pthread	*philo)
{
	ptthread_t	manager;

	pthread_create(&manager, NULL, manager, philo);
	pthread_detach(manager);
	if (!(philo->i & 1))
		usleep(philo->all->t_eat * 1e2);
	while (1)
	{
		sets_fork(philo, 0);
		out(philo, "is eating", 1);
		philo->n_eat += 1;
		usleep(philo->all->t_eat * 1e3);
		sets_fork(philo, 1);
		philo->time[philo->i] = get_time();
		out(philo, "is sleeping", 1);
		usleep(philo->all->t_sleep * 1e3);
		out(philo, "is thinking", 1);
	}
}

void	manager(t_philo *philo, int *pid)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (1)
	{
		if (philo->n_eat)
		{
			if (philo->philos[i].n_eat >= philo->n_eat)
				c++;
			if (c == philo->n_philo)
				ft_exit(pid, philo);
		}
		if (i == philo->n_philo)
		{
			i = 0;
			c = 0;
		}
		if ((get_time() - philo->times[i]) >= philo->t_die + 5)
		{
			out(&philo->philos[i], "died", 0);
			ft_exit(pid, philo);
		}
		i++;
	}
}

int	*ft_thread(t_philo *philo)
{
	int	i;
	int	pid;
	int	*pids;

	sem_unlink("robin");
	sem_unlink("printf");
	philo->robin = sem_open("robin", O_CREAT, 0644, philo->n_philo);
	philo->printf = sem_open("printf", O_CREAT, 0644, 1);
	if (philo->robin == SEM_FAILED || philo->robin == SEM_FAILED)
		exit (0);
	i = -1;
	pids = malloc(sizeof(int) * philo->n_philo);
	while (++i < philo->n_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			func(&philo->philos[i]);
			exit(0);
		}
		else
			pids[i] = pid;
	}
	return (pids);
}

void	ft_exit(int *pid, t_philo *philo, int lamp)
{
	int	i;

	i = -1;
	if (lamp)
		while (++i < philo->n_philo)
			sem_wait(philo->the_me)
	while (++i < philo->n_philo)
		kill(pid[i], SIGTERM);
	exit(0);
}
