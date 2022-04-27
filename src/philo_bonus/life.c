/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:12:48 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:40:08 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print(char *message, t_table *table)
{
	sem_wait(table->sem_print);
	printf("%ld %d %s\n", o_clock(table), table->id, message);
	sem_post(table->sem_print);
}

void	thinking(t_table *table)
{
	print("is thinking", table);
}

void	sleeping(t_table *table)
{
	print("is sleeping", table);
	my_uslip(table, table->t_sleep);
}

void	eating(t_table *table)
{
	sem_wait(table->sem_fork);
	print("has taken a fork", table);
	sem_wait(table->sem_fork);
	print("has taken a fork", table);
	gettimeofday(&table->eatime, NULL);
	print("is eating", table);
	my_uslip(table, table->t_eat);
	sem_post(table->sem_fork);
	sem_post(table->sem_fork);
}
