/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:39:28 by a79856            #+#    #+#             */
/*   Updated: 2022/01/31 14:39:30 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>

typedef struct s_table
{
	struct timeval	startime;
	int				nphilo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				ndinner;
	sem_t			*sem_fork;
	sem_t			*sem_death;
	sem_t			*sem_print;
	int				id;
	int				group;
	struct timeval	eatime;
	int				eated;
	pthread_t		thread;
}	t_table;

void		philo(t_table *table, int id);
void		*philo_dead(void *table);
long int	o_clock(t_table *table);
int			my_uslip(t_table *table, int time);
void		eating(t_table *table);
void		sleeping(t_table *table);
void		thinking(t_table *table);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
int			my_uslip2(int time);
#endif
