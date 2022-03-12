/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:37:37 by ajaidi            #+#    #+#             */
/*   Updated: 2022/03/10 14:57:04 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		r *= 10;
		r += str[i] - 48;
		i++;
	}
	return (r);
}

int	check_in(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (ft_atoi(av[i]) < 1)
			return (0);
	return (1);
}
