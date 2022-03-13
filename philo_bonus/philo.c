/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:33:53 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/08 23:00:38 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	int		*pid;

	if ((ac == 6 || ac == 5) && check_in(ac, av))
	{
		if (!ft_allocation(&philo, av))
			return (printf("Error in allocation\n"), 1);
		pid = ft_thread(&philo);
		sem_close(philo.printf);
		sem_close(philo.robin);
		ft_exit(&philo, pid, 0);
	}
}
