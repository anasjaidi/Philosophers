/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:33:53 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/13 23:00:38 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if ((ac == 6 || ac == 5) && check_in(ac, av))
	{
		if (!ft_allocation(&philo, av))
			return (printf("Eroor in allocation\n"), 0);
		ft_thread(&philo);
		manager(&philo);
		return (ft_free(&philo), 0);
	}
}
