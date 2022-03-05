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

void	*func(void *ph)
{
	t_pthread *philo;
	
	philo = ph;
	if (!(philo->i & 1))
		usleep(1000);
	printf("ok %d\n", philo->i);
	// while (1)
	// {
		
	// }
	return (ph);
}

void	ft_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
		pthread_create(&philo->philos[i].philo , NULL, func, &philo->philos[i]);
	i = -1;
	while (++i < philo->n_philo)
		pthread_detach(philo->philos[i].philo);
}