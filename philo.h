/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/08 20:56:36 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_thread
{
	pthread_t		philo;
	long long		time;
	int				i;
	int				n_eat;
	struct s_philo	*all;
}	t_pthread;

typedef struct s_philo
{
	int					lamp;
	long long			time;
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	pthread_mutex_t		mutex;
	t_pthread			*philos;
	pthread_mutex_t		*forks;
}	t_philo;

int			ft_atoi(const char *str);
int			check_in(int ac, char **av);
void		ft_allocation(t_philo *philo, char **av);
void		ft_thread(t_philo *philo);
void		*manager(t_philo *philo);
void		*func(void *ph);
long long	get_time(void);
void		check_lamp(int ac, t_philo *philo);
void		out(long long time, t_pthread *philo, char *s, int lamp);

#endif