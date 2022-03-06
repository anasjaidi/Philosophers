/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabani <asabani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/06 22:35:18 by asabani          ###   ########.fr       */
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
	int			*lamp;
	pthread_t	philo;
	pthread_mutex_t	*forks;
	long long	time;
	int			i;
	int			n_eat;
	int			n;
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
	t_pthread			*philos;
}	t_philo;

int		ft_atoi(const char *str);
int		check_in(int ac, char **av);
void	ft_allocation(t_philo *philo, char **av);
void	ft_thread(t_philo *philo);

#endif