/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:12:40 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:14:58 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philos_routine(t_table *table)
{
	if (table->group == 2)
		my_uslip2(table->t_eat);
	if (table->group == 3)
		my_uslip2(table->t_eat * 2);
	while (1)
	{
		eating(table);
		sleeping(table);
		thinking(table);
		table->eated++;
		if (table->ndinner && (table->eated == table->ndinner))
			exit (0);
	}
}

static int	my_group(t_table *table)
{
	int	group;

	group = 0;
	if (table->nphilo % 2 != 0 && table->id == table->nphilo
		&& table->nphilo != 1)
		group = 3;
	else if (table->id % 2 != 0)
		group = 1;
	else if (table->id % 2 == 0)
		group = 2;
	return (group);
}

void	philo(t_table *table, int id)
{
	table->id = id;
	table->eatime = table->startime;
	table->group = my_group(table);
	table->eated = 0;
	pthread_create(&table->thread, NULL, &philo_dead, table);
	philos_routine(table);
	pthread_join(table->thread, NULL);
	exit(0);
}
