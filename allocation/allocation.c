/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:48:57 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/04 18:16:22 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_allocation(t_philo *philo, char **av)
{
	philo->n_philo = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->n_eat = ft_atoi(av[5]);
	philo->philos = malloc(sizeof(pthread_t) * philo->n_philo + 1);
	philo->time = malloc(sizeof(long long) * philo->n_philo);
}
