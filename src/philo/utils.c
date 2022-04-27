/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:42:57 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 12:20:21 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	unsigned long int	i;
	int					num;
	int					minus;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == '\n' || str[i] == '\t'
		|| str[i] == ' ' || str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		++i;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus *= -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		++i;
	}
	return (num * minus);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_all_digit(char *argv)
{
	int	y;

	y = 0;
	while (argv[y])
	{
		if (!(ft_isdigit(argv[y])))
			return (0);
		y++;
	}
	return (1);
}

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (-1);
}

void	free_mem(t_threads *table, t_forks *forks)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&forks[i].mutex);
	free(forks);
	free(table->thread);
	pthread_mutex_destroy(table->deadlock);
	free(table->deadlock);
}
