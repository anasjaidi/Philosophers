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

int	func(t_pthread *philo)
{
	pthread_t	procces;

	pthread_create(&procces, NULL, ft_procces, philo);
	pthread_detach(procces);
	while (1)
	{
		if (philo->all->n_eat)
		{
			if (philo->n_eat >= philo->all->n_eat)
				ft_free(philo->all, 0);
		}
		if ((get_time() - philo->time) > philo->all->t_die)
		{
			out(philo, "died", 0);
			ft_free(philo->all, 1);
		}
		usleep(50);
	}
}

void	*ft_procces(void *ph)
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
			func(&philo->philos[i]);
		else
			pids[i] = pid;
	}
	return (pids);
}

void	ft_exit(t_philo *philo, int *pid, int size)
{
	int	i;
	int	status;

	if (size == philo->n_philo)
		return (free(pid), ft_free(philo, 0));
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < philo->n_philo)
				kill(pid[i], SIGKILL);
		}
		else
			return (ft_exit(philo, pid, size + 1));
	}
	else
	{
		i = -1;
		while (++i < philo->n_philo)
			kill(pid[i], SIGKILL);
	}
	return (free(pid), ft_free(philo, 0));
}
