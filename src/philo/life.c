/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:23:43 by a79856            #+#    #+#             */
/*   Updated: 2022/02/01 03:02:15 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_fork_and_return(t_p *philo)
{
	int	fork;

	if (any_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->forks[philo->id_p - 1].mutex);
	if (!(ft_write(philo, "has taken a fork\n", o_clock(philo))))
	{
		pthread_mutex_unlock(&philo->forks[philo->id_p - 1].mutex);
		return (1);
	}
	if (philo->table->philo_num == 1)
		return (1);
	if (philo->id_p == 1)
		fork = philo->table->philo_num - 1;
	else
		fork = philo->id_p - 2;
	pthread_mutex_lock(&philo->forks[fork].mutex);
	if (!(ft_write(philo, "has taken a fork\n", o_clock(philo))))
	{
		pthread_mutex_unlock(&philo->forks[fork].mutex);
		return (1);
	}
	return (0);
}

static void	put_fork(t_p *philo)
{
	int	fork;

	pthread_mutex_unlock(&philo->forks[philo->id_p - 1].mutex);
	if (philo->id_p == 1)
		fork = philo->table->philo_num - 1;
	else
		fork = philo->id_p - 2;
	pthread_mutex_unlock(&philo->forks[fork].mutex);
}

int	thinking(t_p *philo)
{
	if (any_dead(philo))
		return (1);
	if (ft_write(philo, "is thinking\n", o_clock(philo)))
		return (0);
	if ((philo->table->time_to_eat - philo->table->time_to_sleep) > 0)
		my_uslip(philo->table->time_to_eat - philo->table->time_to_sleep);
	return (1);
}

int	sleeping(t_p *philo)
{
	if (!(any_dead(philo)))
	{
		if (ft_write(philo, "is sleeping\n", o_clock(philo)))
		{
			if (my_uslip(philo->table->time_to_sleep))
				return (1);
		}
		return (0);
	}
	return (1);
}

int	eating(t_p *philo)
{
	if (get_fork_and_return(philo))
		return (1);
	gettimeofday(&philo->eatime, NULL);
	if (ft_write(philo, "is eating\n", o_clock(philo)))
	{
		if (my_uslip(philo->table->time_to_eat))
			return (1);
	}
	put_fork(philo);
	philo->eat++;
	return (0);
}
