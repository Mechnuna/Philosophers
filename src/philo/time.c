/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:15:07 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 12:33:22 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_p *philo)
{
	struct timeval	now;
	long int		period;

	gettimeofday(&now, NULL);
	period = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (philo->eatime.tv_sec * 1000 + philo->eatime.tv_usec / 1000);
	if (period > philo->table->time_to_die)
		return (1);
	return (0);
}

int	any_dead(t_p *philo)
{
	pthread_mutex_lock(philo->table->deadlock);
	if (philo->table->death)
	{
		pthread_mutex_unlock(philo->table->deadlock);
		return (1);
	}
	if (is_dead(philo))
	{
		philo->table->death = 1;
		pthread_mutex_unlock(philo->table->deadlock);
		printf("%ld %d died\n", o_clock(philo), philo->id_p);
		return (1);
	}
	pthread_mutex_unlock(philo->table->deadlock);
	return (0);
}

long int	o_clock(t_p *philo)
{
	struct timeval	now;
	long int		ms;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec * 1000 + now.tv_usec / 1000)
		- (philo->table->star_time.tv_sec * 1000
			+ philo->table->star_time.tv_usec / 1000);
	return (ms);
}

unsigned long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	my_uslip(int time)
{
	unsigned long	start;
	unsigned long	now;

	start = get_time_ms();
	now = start;
	while (now < start + time)
	{
		usleep(SLEEP);
		now = get_time_ms();
	}
	return (0);
}
