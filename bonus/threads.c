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

void	*ft_manager(void *ph)
{
	t_pthread	*philo;
	int			i;

	philo = ph;
	i = -1;
	while (1)
	{
		if (philo->all->n_eat)
		{
			if (philo->n_eat >= philo->all->n_eat)
			{
				sem_post(philo->all->the_me);
				return (NULL);
			}
		}
		if ((get_time() - philo->time) >= philo->all->t_die + 5)
		{
			out(philo, "died", 0);
			while (++i < philo->all->n_philo)
				sem_post(philo->all->the_me);
		}
	}
}

void	func(t_pthread	*philo)
{
	pthread_t	manager;

	pthread_create(&manager, NULL, ft_manager, philo);
	pthread_detach(manager);
	if (!(philo->i & 1))
		usleep(philo->all->t_eat * 1e2);
	while (1)
	{
		sets_fork(philo, 0);
		out(philo, "is eating", 1);
		usleep(philo->all->t_eat * 1e3);
		sets_fork(philo, 1);
		philo->time = get_time();
		out(philo, "is sleeping", 1);
		usleep(philo->all->t_sleep * 1e3);
		out(philo, "is thinking", 1);
		philo->n_eat += 1;
	}
}

void	ft_sem_init(t_philo *philo)
{
	sem_unlink("robin");
	sem_unlink("printf");
	sem_unlink("the_me");
	philo->robin = sem_open("robin", O_CREAT, 0644, philo->n_philo);
	philo->printf = sem_open("printf", O_CREAT, 0644, 1);
	philo->the_me = sem_open("the_me", O_CREAT, 0644, 0);
	if (philo->robin == SEM_FAILED || philo->robin == SEM_FAILED || philo->the_me == SEM_FAILED)
		exit (0);
}

int	*ft_thread(t_philo *philo)
{
	int	i;
	int	pid;
	int	*pids;

	ft_sem_init(philo);
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

void	ft_exit(t_philo *philo, int *pid)
{
	int	i;

	i = -1;
	// while (++i < philo->n_philo)
	// 	sem_wait(philo->the_me);
	while (++i < philo->n_philo)
		kill(pid[i], SIGTERM);
	exit(0);
}
