/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:34:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/05 20:49:13 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_thread
{
	pthread_t	philo;
	long long	time;
	int			i;
	int			n_eat;
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
}	t_philo;

int		ft_atoi(const char *str);
int		check_in(int ac, char **av);
void	ft_allocation(t_philo *philo, char **av);
void	ft_thread(t_philo *philo);

#endif