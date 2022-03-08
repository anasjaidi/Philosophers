/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:33:53 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/08 21:17:43 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if ((ac == 6 || ac == 5) && check_in(ac, av))
	{
		check_lamp(ac, &philo);
		ft_allocation(&philo, av);
		ft_thread(&philo);
		manager(&philo);
		while (philo.lamp !=2)
			usleep(1);		
	}
}
