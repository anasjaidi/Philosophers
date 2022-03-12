/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/08 23:12:06 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_thread
{
	pthread_t		philo;
	long long		*time;
	int				i;
	int				n_eat;
	struct s_philo	*all;
}	t_pthread;

typedef struct s_philo
{
	long long			time;
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	t_pthread			*philos;
	sem_t				*printf;
	sem_t				*robin;
	long long			*times;
}	t_philo;

int			ft_atoi(const char *str);
int			check_in(int ac, char **av);
void		ft_allocation(t_philo *philo, char **av);
int			*ft_thread(t_philo *philo);
void		manager(t_philo *philo, int *pid);
void		func(t_pthread *philo);
long long	get_time(void);
void		out(t_pthread *philo, char *s, int lamp);
void		ft_exit(int *pid, t_philo *philo);

#endif