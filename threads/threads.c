/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:29:41 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/04 19:53:44 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*func(void *ph)
{
	
	while (1)
	{
		/* code */
	}
	
	return (ph);
}

void	ft_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philo)
		pthread_create(&philo->philos[i], NULL, func, (void*)philo);
	i = -1;
	while (++i < philo->n_philo)
		pthread_join(philo->philos[i], NULL);
}